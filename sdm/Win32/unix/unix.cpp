// This is the main DLL file.
#include <unistd.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <pthread.h>

#undef chmod
#undef close
#undef read
#undef write
#undef lseek

#include <io.h>
#include <unix/fcntl.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

struct FilePair
{
	char* name;
	int reader, writer;
	int timeout, length;
	bool versionSent;
};
static int numFilePairs = 1;
static struct FilePair** filePairs;
#define FILE_PAIR_BASE 10000
pthread_mutex_t fileTableMutex = PTHREAD_MUTEX_INITIALIZER;

SDMLIB_API void chdir( const char* newDirectory )
{
	SetCurrentDirectory(newDirectory);
}

SDMLIB_API int wChmod( const char* filename, int mode )
{
	return _chmod(filename,mode);
}


SDMLIB_API int wClose( int fd )
{
	if ( fd > FILE_PAIR_BASE )
	{
		pthread_mutex_lock( &fileTableMutex );
		if ( fd-FILE_PAIR_BASE >= numFilePairs )
		{
			errno = EINVAL;
			pthread_mutex_unlock( &fileTableMutex );
			return -1;
		}
		struct FilePair* fp = filePairs[fd-FILE_PAIR_BASE];
		pthread_mutex_unlock ( &fileTableMutex );
		if( fp->reader > 0 )
		{
			_close( fp->reader);
		}
		int status = 0;
		if(fp->writer > 0)
		{
			status = _close(fp->writer);
		}
		free(fp->name);
		fp->name = NULL;
		fp->reader = fp->writer = -1;
		return status;
	}
	return _close(fd);
}

SDMLIB_API int fcntl( int fd, unsigned int op, unsigned int flags)
{
	if ( op != F_SETFL || flags != O_NONBLOCK )
		printf("fcntl(%d,%d,0x%0x)\n",fd,op,flags);
	return 0;
}

SDMLIB_API int fcntl( int fd, unsigned int flags)
{
	if ( flags != O_NONBLOCK )
		printf("fcntl(%d,0x%0x)\n",fd,flags);
	return 0;
}

static int pid = 77;
SDMLIB_API pid_t fork()
{
	printf("fork() = %d\n",pid);
	return pid++;
}

SDMLIB_API int ioctl(int fd, uint op, ...)
{
	int value;
	DWORD returnedLength;
	char outBuf[16];
	va_list marker;
	va_start( marker, op );     /* Initialize variable arguments. */
	value = va_arg( marker, int);
	va_end( marker );              /* Reset variable arguments.      */
//	printf("ioctl(%d,%d,0x%0x)\n", fd, op, value);
//	*(int*)inBuf = value;
	if ( fd > FILE_PAIR_BASE )
	{
		if ( fd-FILE_PAIR_BASE >= numFilePairs )
		{
			errno = EINVAL;
			pthread_mutex_unlock( &fileTableMutex );
			return -1;
		}
		if ( op & 0xC000 )
		{
			struct FilePair* fp = filePairs[fd-FILE_PAIR_BASE];
			pthread_mutex_unlock( &fileTableMutex );
			switch ( op )
			{
			case 0xC001:
				*(int*)value = 1;
				break;
			case 0xC002:
				fp->timeout = value;
				break;
			case 0xC003:
				printf("\nDon't understand RobustHub command for %s\n\n", fp->name);
				break;
			case 0xC004:
				char* path = (char*)value;
				int port = fp->name[strlen(fp->name)-1] - '0';
				sprintf(path,"port %d.%d", port/4,port%4);
				break;
			}
		}
	}
	BOOL status = DeviceIoControl( (HANDLE)fd, op, (void*)&value, 4, outBuf, sizeof(outBuf), &returnedLength, NULL);
//	value = *(int*)outBuf;
	return 0;
}

SDMLIB_API int open( const char* filepath, unsigned int flags)
{
	if ( strncmp(filepath,"/dev/asim",9) == 0 )
	{
		struct FilePair* fp = NULL;
		pthread_mutex_lock( &fileTableMutex );
		int fd;
		for( fd=1; fd < numFilePairs; fd++ )
		{
			if ( filePairs[fd] != NULL && filePairs[fd]->name == NULL )
			{
				fp = filePairs[fd];
				fd += FILE_PAIR_BASE;
				break;
			}
		}
		if ( fp == NULL )
		{
			fp = (struct FilePair*)calloc(sizeof(struct FilePair),1);
			filePairs = (struct FilePair**)realloc( filePairs, (numFilePairs+1)*sizeof(struct FilePair*));
			filePairs[numFilePairs] = fp;
			fd = FILE_PAIR_BASE+numFilePairs++;
		}
		fp->name = strdup(filepath);
		pthread_mutex_unlock( &fileTableMutex );
		char name[64];
		strcpy(name,filepath);
		strcat(name,".r");
		fp->reader = _open(name,flags|_O_BINARY);
		strcpy(name,filepath);
		strcat(name,".w");
		fp->writer = _open(name,flags|_O_BINARY);
		return fd;
	}
	return _open(filepath,flags,_S_IREAD | _S_IWRITE);
}

SDMLIB_API int pipe( int fd[2])
{
	return _pipe( fd, 256*1024, _O_BINARY );
}

SDMLIB_API int wRead(int fd, void* buf, int len)
{
	if ( fd > FILE_PAIR_BASE )
	{
		pthread_mutex_lock( &fileTableMutex );
		if ( fd-FILE_PAIR_BASE >= numFilePairs )
		{
			errno = EINVAL;
			pthread_mutex_unlock( &fileTableMutex );
			return -1;
		}
		struct FilePair* fp = filePairs[fd-FILE_PAIR_BASE];
		pthread_mutex_unlock( &fileTableMutex );
		if ( fp->reader == -1 ) return 0;
		char buffer[70];
		int i, offset, n;
		char* chars = (char*)buf;
AGAIN:
		buffer[0] = buffer[1] = buffer[2] = 0;
		do {
			n = _read(fp->reader,buffer,6);
			chars[0] = buffer[0];
			if ( n > 3 )
			{
				if ( '0' <= buffer[1] && buffer[1] <= '9'
					&& '0' <= buffer[2] && buffer[2] <= '9'
					&& '0' <= buffer[3] && buffer[3] <= '9'
					&& '0' <= buffer[4] && buffer[4] <= '9'
					&& '0' <= buffer[5] && buffer[5] <= '9' )
				{
					sscanf(&buffer[1], "%5d", &fp->length );

					if ( fp->versionSent )
					{
						chars[1] = fp->length/256;
						chars[2] = fp->length%256;
					}
					else
					{
						chars[2] = fp->length/256;
						chars[1] = fp->length%256;
					}
					offset = 3;
					switch ( chars[0] )
					{
					case 'T':
						Sleep(fp->length);
						fp->length = 0;
						break;
					case 'V':
						fp->versionSent = true;
						break;
          default:
            break;
					}
				}
				else
				{
					offset = 6;
					for( i=0; i<offset; i++)
						chars[i] = buffer[i];
				}

				if ( fp->length >= 0 )
				{
					int m = fp->length+2;
					if ( len-offset < fp->length )
						m = len-offset;
					n = _read(fp->reader,&chars[offset],m) + offset;
					if ( chars[0] == 'T' )
						goto AGAIN;
				}
				else
					n = offset;
				return n;
			}
			if ( n == 0 )
				Sleep(1000);
		} while ( n == 0 );
		return n;
	}
	return _read(fd, buf, len);
}

SDMLIB_API void sleep( unsigned int seconds )
{
	Sleep(seconds*1000);
}

SDMLIB_API char* strerror_r(int errornum, char* buf, size_t len)
{
	int error = *_errno();

	if ( error < _sys_nerr )
		strncpy(buf,_sys_errlist[error],len);
	else
		sprintf(buf,"errno, %d, out of range, %d",error,_sys_nerr);
	return buf;
}

SDMLIB_API char* strndup( const char* str, size_t n )
{
	size_t len = strlen(str);
	if ( len > n )
	{
		char* dup = (char*)malloc(n+1);
		strncpy(dup,str,n);
		dup[n] = 0;
		return dup;
	}
	else
		return strdup(str);
}

SDMLIB_API void usleep(unsigned int microsec)
{
	if ( microsec%1000 != 0 )
		{
		//printf("usleep(%d)\n",microsec);
		}
	Sleep(microsec/1000);
}

SDMLIB_API int wait( int* status )
{
	*status = 0;
	printf("wait(%d)\n",*status);
	return 0;
}

SDMLIB_API int wWrite(int fd, const void* buf, int len)
{
	if ( fd > FILE_PAIR_BASE )
	{
		pthread_mutex_lock( &fileTableMutex );
		if ( fd-FILE_PAIR_BASE >= numFilePairs )
		{
			errno = EINVAL;
			pthread_mutex_unlock( &fileTableMutex );
			return -1;
		}
		struct FilePair* fp = filePairs[fd-FILE_PAIR_BASE];
		pthread_mutex_unlock( &fileTableMutex );
		if ( fp->writer == -1 ) return 0;
		fd = fp->writer;
	}
	return _write(fd, buf, len);
}

SDMLIB_API int wLseek(int _FileHandle, long _Offset, int _Origin)
{
	return _lseek(_FileHandle,_Offset,_Origin);
}
