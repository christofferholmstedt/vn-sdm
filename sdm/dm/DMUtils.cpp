// Extra utility functions used by the Data Manager

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifdef __VXWORKS__
#include <sockLib.h>
#include <ioLib.h>
#endif

#include "../common/message/SDMxTEDS.h"
#include "DMUtils.h"

#ifdef SEND_IMA
#include <netinet/in.h>
#include <netspwpnp/spwpnp.h>
#endif


/*
	Description:
		Is the xTEDS from an ASIM (ie negative (MSB set))?

	Input:
		processID	- ASIM PID (ie negative, less than zero)

	Output:
		true - if processID is negative
		false - if processID is non-negative

	Changed:
		None

	Written by:	Kelly Wheeler
	Date:		04/17/07
*/
bool IsPIDFromASIM (long processID)
{
	if (processID < 0)
		return true;
	else
		return false;
}


/*
	Description:
		Convert a processID to a filename.

	Input:
		processID	- ASIM PID (ie negative, less than zero)
		fileName - pointer for output conversion

	Output:
		true - if fileName is valid
		false - if fileName is invalid

	Changed:
		fileName as a string, or null if failed.

	Written by:	Kelly Wheeler
	Date:		04/17/07
*/
bool PIDToFileName (long processID, char fileName[])
{
	if (IsPIDFromASIM (processID))
	{
		sprintf (fileName, "./xTEDS/%ld.xml", processID * -1);	// convert processID to filename
		return true;
	}
	else
		return false;
}


/*
	Description:
		Write an xTEDS to the file system using processID as the name

	Input:
		long processID - the ASIM's PID type to be used as name of the stored xTEDS file
		char* xTEDSIn - valid xTEDS to store in filesystem

	Output:
		error:
		0 - Success
		-1 - PID is not from ASIM
		-2 - Unable to open xTEDS file of given PID
		-3 - No bytes written to file

	Changed:
		- new file created in xTEDS directory using the input's processID as the file name.  ie. -34 = 34.xml

	Written by:	Kelly Wheeler
	Date:		04/17/07
*/
int Store_xTEDS (long processID, char* xTEDSIn)
{
	char fileName[FILENAME_SIZE];							// xTEDS filename with .xml extension
	int bytesWritten;										// number of bytes written
	int fd = 0;												// file descriptor
	char endOfLine = '\n';


	if (!PIDToFileName (processID, fileName))						// convert processID to filename
	{
		printf ("\tStore_xTEDS:  processID is not from ASIM\n\n");
		return -1;											// return error -1
	}
#ifdef WIN32
	fd = open (fileName, O_RDWR | O_CREAT);					// open storage file for writing
#else
	fd = open (fileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
#endif

	if(fd == -1)											// Can't open filename?
	{
		perror("Store_xTEDS:  Unable to open ASIM xTEDS file! ");
		return -2;											// return error -2
	}

	bytesWritten = write(fd, xTEDSIn, strlen(xTEDSIn));		// write xTEDS to file

	bytesWritten = write(fd, &endOfLine, 1);				// end the file

	close(fd);												// close the file

	if (bytesWritten < 0)									// did anything actually get written?
		return -3;											// No - return -3
	else
		return 0;										// Yes - return true
}


/*
	Description:
		Read an xTEDS from the file system using processID as the name

	Input:
		long processID - the ASIM's PID (ie negative, less than zero) type to be used as name of the stored xTEDS file

	Output:
		0 - Success
		-1 - PID is not from ASIM
		-2 - Unable to open xTEDS file of given PID

	Changed:
		char* xTEDSOut - xTEDS from filesystem, but not validated.  Or NULL if unread.

	Written by:	Kelly Wheeler
	Date:		04/17/07
*/
int Retrieve_xTEDS (long processID, char* xTEDSOut)
{
	char fileName[FILENAME_SIZE];							// xTEDS filename with .xml extension
	int bytesRead;											// number of bytes read
	int fd = 0;												// file descriptor


	if (!PIDToFileName (processID, fileName))						// convert PID to filename
	{
		printf ("\tRetrieve_xTEDS:  processID is not from ASIM\n\n");
		return -1;											// return error -1
	}

	fd = open(fileName,O_RDONLY);							// open the xTEDS file for reading
	if(fd == -1)											// if open failed return error
	{
		perror("Unable to open ASIM xTEDS file! ");
		return -2;											// return error -2
	}

	bytesRead = read(fd, xTEDSOut, MAX_XTEDS_SIZE);			// read the whole file at once

	close(fd);												// close the xTEDS file
	xTEDSOut[bytesRead] = '\0';								// end the buffer string

	return 0;											// return true
}

#ifdef SEND_IMA
int SendIMA(unsigned char which, int debug)
{
  int sock;
  struct sockaddr_spwpnp sspwpnp;

  struct hostent *he;
  struct in_addr *nm_addr;
  struct in_addr *lh_addr;

  struct spwpnp_ima ima;

  unsigned long nm_addr_host;
  unsigned long lh_addr_host;

  int sent;

   while ((he=gethostbyname("localhost.spacewire")) == NULL)
   {
      if (debug >= 1)
      {
         printf("gethostbyname failed for localhost.spacewire. Retrying in 5 secs.\n");
      }
      sleep(5);
   }
   lh_addr = (struct in_addr*)he->h_addr;
   lh_addr_host = ntohl(lh_addr->s_addr);

   if (debug >= 2)
   {
      printf("Got localhost address %s\n", inet_ntoa(*lh_addr));
   }

   while ((he=gethostbyname("networkmanager.spacewire")) == NULL)
   {
      if (debug >= 1)
      {
         printf("gethostbyname failed for networkmanager.spacewire. Retrying in 5 secs.\n");
      }
      sleep(5);
   }
   nm_addr = (struct in_addr*)he->h_addr;
   nm_addr_host = ntohl(nm_addr->s_addr);

   if (debug >= 2)
   {
      printf("Got NetworkManager address %s\n", inet_ntoa(*nm_addr));
   }

   /*
    * As defined, we translate an ip to a router id and router port:
    *   10.x.x.y  --> xx = router id, y = router port
    *
    */
   memset(&sspwpnp, 0, sizeof(sspwpnp));
   sspwpnp.sspwpnp_family = AF_SPWPNP;
   sspwpnp.sspwpnp_router_id = htons((nm_addr_host >> 8) & 0xFFFF);
   sspwpnp.sspwpnp_router_port = (nm_addr_host & 0xFF);

   sock = socket(PF_SPWPNP, SOCK_DGRAM, SPWPNPPROTO_ANY);
   if (sock <0 )
   {
      perror("socket");
      return -1;
   }

   ima.hdr.logical_addr   = LogicalAddrAny;
   ima.hdr.protocol_id    = ProtocolLl;
   ima.hdr.packet_type    = PacketNetworkManager;
   ima.hdr.data_type      = DataIma;
   ima.hdr.transaction_id = which;
   ima.hdr.data_select    = ImaPrimary;
   ima.hdr.data_len       = htons(sizeof(ima) - sizeof(ima.hdr) - sizeof(ima.csum));
   ima.ip                 = htonl(lh_addr_host);
   ima.port               = htons(PORT_DM);
   ima.csum               = 0;

   printf("sending ima host 0x%x port %d size %d\n", ntohl(ima.ip), ntohs(ima.port), sizeof(ima));

   sent = sendto(sock, &ima, sizeof(ima), 0, (struct sockaddr*)&sspwpnp, sizeof(sspwpnp));
   if (sent < 0)
   {
      perror("sendto");
      return -1;
   }

   if (debug >= 2)
   {
      printf("Sent IMA\n");
   }

   return 0;
}
#endif

/* GetNodeAddress sets the IP address of the DataManager in the global Address_DM.
	Returns: unsigned long - The address of the current node, or zero if an error occurred
*/
#ifdef WIN32
unsigned long GetNodeAddress(bool spacewire)
{
	hostent * localHost;
	char hostname[64];
	char * IPAddr;
	unsigned long Address = 0;

	if (gethostname(hostname,sizeof(hostname)) < 0)
		return 0;

	if ((localHost = gethostbyname(hostname)) == NULL)
		return 0;

	IPAddr = inet_ntoa(*(struct in_addr *)localHost->h_addr_list[0]);
	Address = inet_addr(IPAddr);
	return Address;
}
#else

#ifdef __uClinux__
#warning "uClinux GetNodeAddress"
unsigned long GetNodeAddress(bool spacewire)
{
  unsigned long Address = 0;

  if (spacewire) {
    struct hostent *he;

    while ((he=gethostbyname("localhost.spacewire")) == NULL) {
      sleep(1);
    }

    memcpy(&Address, he->h_addr, sizeof(Address));
  }
  else {
    struct ifreq ifr;
    struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
    int sockfd;

    bzero(&ifr, sizeof(ifr));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
	perror("socket()");
	return(0);
      }
    strcpy(ifr.ifr_name, "eth0");
    sin->sin_family = AF_INET;
    if(ioctl(sockfd, SIOCGIFADDR, &ifr) == 0)
      {
	Address = inet_addr(inet_ntoa(sin->sin_addr));
      }
    close(sockfd);
  }
  return Address;
}

#else /* Linux, default */
unsigned long GetNodeAddress(bool spacewire)
{
	struct ifreq ifr;
     	struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
     	int sockfd;
	unsigned long Address = 0;

	memset(&ifr, 0, sizeof(ifr));
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		return(0);
	}

#ifdef __VXWORKS__
	strcpy(ifr.ifr_name, "rxg0");
#else
	strcpy(ifr.ifr_name, "eth0");
#endif
	sin->sin_family = AF_INET;
	if(ioctl(sockfd, SIOCGIFADDR, &ifr) == 0)
	{
		Address = inet_addr(inet_ntoa(sin->sin_addr));
	}
	close(sockfd);
	return Address;
}
#endif
#endif

void CreatexTEDSDirectory()
{
#ifdef WIN32
	DWORD exists = GetFileAttributes(".\\xTEDS");
	if(exists == 0xFFFFFFFF)
		system("mkdir .\\xTEDS");				// make the xTEDS backup directory or fail if exists
#else
	struct stat folder;
	if(stat("xTEDS",&folder) < 0)
		system("mkdir xTEDS");					// make the xTEDS backup directory or fail if exists
#endif
}

