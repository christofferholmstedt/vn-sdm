#include "../common/asim/ASIM.h"
#include "../common/message_defs.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <curses.h>

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MENU_WIDTH	23
#define MENU_HEIGHT	17

ASIM sensor;

bool RawMode;
int cur_line = 1;

WINDOW* w_menu;
WINDOW* w_in;
WINDOW* w_out;

void menu();
void init();
void reset();
void selftest();
void data();
void stream();
void poweron();
void powerdown();
void version();
void asim_command();
void xteds();
void cancel();
void timeattone();
void rawmodetoggle();

void* Listener(void*);

void drawGUI(void);
void drawMenu(void);
void drawInput(void);
void drawOutput(void);
void displayRead(void);
void displayRaw(void);

int main(int argc,char** argv)
{
	pthread_t listener_thread;
	RawMode = false;
	if (argc == 3)
	{
		if(strcmp(argv[2],"debug")==0)
		sensor.SetDebug(4);
	}
	if (argc >= 2)
	{
		fflush(NULL);
		if(!sensor.Open(argv[1]))
		{
			printf("Error: Could not open device %s\n",argv[1]);
			_exit(0);
		}
		fflush(NULL);
		if(!sensor.VerifyConnection())
		{
			printf("Error: Could not verify connection\n");
			_exit(0);
		}

	}	
	else
	{
		printf ("ASIM Tester %s\n",SDM_VERSION);
		printf("Usage: %s device [debug]\n",argv[0]);
		_exit(0);
	}
	
	/* initialize curses*/
	initscr();
	keypad(stdscr,TRUE);
	nonl();
	cbreak();
	noecho();

	drawGUI();
	pthread_create(&listener_thread,NULL,&Listener,NULL);
	sleep(2);
	//reset();
	//sleep(1);
	init();
	sleep(1);
	version();
	while(1)
		menu();
	pthread_join(listener_thread,NULL);
	return 0;
}

void displayRaw(void)
{
	char buf[BUFSIZE];
	short length;
	int i;
	
	int error_code;
	char error_str[80];	

	length = sensor.RawRead((unsigned char*)buf);

	
	if (cur_line >= LINES-4)
	{
		cur_line  = 1;
		drawOutput();
	}
	error_code = errno;
	wmove(w_out,cur_line,1);
	
	if(length < 0)
	{	
		wprintw(w_out,"ASIM read error: %s",strerror_r(error_code,error_str,80));
	}
	else
	{
		wprintw(w_out,"%d bytes",length);
		if(isprint(buf[0]))
		{
			wprintw(w_out," (%c)",buf[0]);
		}
		wprintw(w_out,"%s",":\t");
		for(i=0;i<length;i++)
			wprintw(w_out,"%.2hhx ",buf[i]);
	}
	cur_line++;	
	wrefresh(w_out);
}

void displayRead(void)
{
	char buf[BUFSIZE];
	unsigned short length;
	int i;

	char msg_type;
	
	int error_code;
	char error_str[80];	

	msg_type = sensor.Read(length,(unsigned char*)buf, sizeof(buf));

	if (cur_line >= LINES-4)
	{
		cur_line  = 1;
		drawOutput();
	}

	error_code = errno;
	switch(msg_type)		
	{
	case ASIM_STATUS:
		wmove(w_out,cur_line,1);
		if (buf[0]&0x80) //first bit is set for an error
		{
			wprintw(w_out,"ASIM status ERROR: %hhd",buf[0]);			
			if(buf[0]&0x40) //illegal command bit
			{
				cur_line++;
				wmove(w_out,cur_line,1);
				wprintw(w_out,"Illegal or unrecognized command");
			}
			if(buf[0]&0x20) //self test failure bit
			{
				cur_line++;
				wmove(w_out,cur_line,1);
				wprintw(w_out,"Self Test failed");
			}
		}
		else
		{
			wprintw(w_out,"ASIM status OK: %hhd",buf[0]);
		}
		if(buf[0]&0x10) //mode bit
		{
			cur_line++;
			wmove(w_out,cur_line,1);
			wprintw(w_out,"ASIM mode: operational");
		}
		else
		{
			cur_line++;
			wmove(w_out,cur_line,1);
			wprintw(w_out,"ASIM mode: idle");
		}		
		cur_line++;
		break;
	case ASIM_XTEDS:
		//clear output screen for the xTEDS
		cur_line  = 1;
		drawOutput();
		//display xTEDS
		wmove(w_out,cur_line,1);
		wprintw(w_out,"ASIM xTEDS (%d):",length);
		cur_line++;
		wmove(w_out,cur_line,1);
		cur_line++;
		for(i=0;i<length;++i)
		{
			if(isprint(buf[i]))
			{
				wprintw(w_out,"%c",buf[i]);
			}
			else
			{
				if(iscntrl(buf[i]))
				{
					if(buf[i] == '\n')
					{
						wmove(w_out,cur_line,1);
						cur_line++;
					}
					if(buf[i] == '\t')
					{
						wprintw(w_out,"   ");
					}
				}
				else
				{
					wmove(w_out,1,13);
					wprintw(w_out,"ERROR: contains non-prinatble character 0x%hhx",buf[i]);
					wmove(w_out,cur_line,1);
					cur_line++;
				}
			}
		}
		cur_line++;
		break;
	case ASIM_DATA:
		wmove(w_out,cur_line,1);
		wprintw(w_out,"ASIM data message (%d bytes): (%hhd,%hhd)",length,buf[0],buf[1]);
		cur_line++;
		wmove(w_out,cur_line,1);
		for(i=0;i<length-1;++i)
		{
			wprintw(w_out,"%hhx ",buf[1+i]);
		}
		cur_line++;
		break;
	case ASIM_VERSION:
		wmove(w_out,cur_line,1);
		wprintw(w_out,"ASIM version %hhd",buf[0]);
		cur_line++;
		break;
	case ASIM_ERROR:
		wmove(w_out,cur_line,1);
		wprintw(w_out,"ASIM read error: %s",strerror_r(error_code,error_str,80));
		cur_line++;
		break;
	case ASIM_TIMEOUT:		
		wmove(w_out,cur_line,1);
		wprintw(w_out,"ASIM read error: %s",strerror_r(error_code,error_str,80));
		cur_line++;
		break;
	default:			
		wmove(w_out,cur_line,1);
		wprintw(w_out,"Unexpected ASIM message");
		cur_line++;
		wmove(w_out,cur_line,1);
		wprintw(w_out,"%hhx %hd ",msg_type,length);
		for(i=0;i<length;++i)
		{
			wprintw(w_out,"%hhx ",buf[i]);
		}
		cur_line++;
		break;
	}
	wrefresh(w_out);

}

void* Listener(void*)
{
	while(1)
	{
		if(RawMode)
		{
			displayRaw();
		}
		else
		{
			displayRead();
		}
	}
	return NULL;
}

void drawGUI(void)
{
	//make main border with title
	box(stdscr,0,0);
	move(0,1);
	wprintw(stdscr,"ASIM Tester %s",SDM_VERSION);
	w_menu = subwin(stdscr,MENU_HEIGHT,MENU_WIDTH,1,1);
	w_out = subwin(stdscr,LINES-2,COLS-2-MENU_WIDTH,1,MENU_WIDTH+1);
	w_in = subwin(stdscr,LINES-2-MENU_HEIGHT,MENU_WIDTH,MENU_HEIGHT+1,1);
	drawInput();
	drawOutput();
	drawMenu();
	wrefresh(stdscr);
}

void drawInput(void)
{
	werase(w_in);
	box(w_in,0,0);
	wmove(w_in,0,1);
	waddstr(w_in,"ASIM Input");
	wrefresh(w_in);
}

void drawOutput(void)
{
	werase(w_out);
	box(w_out,0,0);
	wmove(w_out,0,1);
	wprintw(w_out,"ASIM Output (USB path:%s) ",sensor.USBLocation());
	if(RawMode)
		wprintw(w_out,"%s","Raw Mode");
	wrefresh(w_out);
}

void drawMenu(void)
{
	int ITEMS = 15;
	int i;
	char* menu[]={
		"(I)nitialize","(R)eset","(S)tream request",
		"(P)ower On","Power (D)own","(V)ersion request",
		"Co(m)mand","(x)TEDS request","Time at T(o)ne",
		"Self (T)est","D(a)ta request","(C)ancel stream"," ","Ra(w) Mode","(Q)uit"
		};

	//make menu border with title
	box(w_menu,0,0);
	//wmove(w_menu,0,1);
	//waddstr(w_menu,"Menu");
	//make menu
	for(i=0;i<ITEMS;i++)
	{
		wmove(w_menu,i+1,1);
		waddstr(w_menu,menu[i]);
	}
	wrefresh(w_menu);
}

void menu(void)
{
	char command;
	while(1)
	{
		command = getch();
	
		switch(command)
		{
		case 'I':
		case 'i':
			init();
			break;
		case 'R':
		case 'r':
			reset();
			break;
		case 'T':
		case 't':
			selftest();
			break;
		case 'A':
		case 'a':
			data();
			break;
		case 'S':
		case 's':
			stream();
			break;
		case 'P':
		case 'p':
			poweron();
			break;
		case 'D':
		case 'd':
			powerdown();
			break;
		case 'V':
		case 'v':
			version();
			break;
		case 'M':
		case 'm':
			asim_command();
			break;
		case 'X':
		case 'x':
			xteds();
			break;
		case 'O':
		case 'o':
			timeattone();
			break;
		case 'C':
		case 'c':
			cancel();
			break;
		case 'Q':
		case 'q':
			endwin();
			_exit(0);
		case 'W':
		case 'w':
			rawmodetoggle();
			break;
		default:
			wprintw(w_out,"Bad Command\n");
		}
	}
}

void rawmodetoggle()
{
	RawMode = !RawMode;
	box(w_out,0,0);
	wmove(w_out,0,1);
	wprintw(w_out,"ASIM Output (USB path:%s) ",sensor.USBLocation());
	if(RawMode)
		wprintw(w_out,"%s","Raw Mode");
	wrefresh(w_out);
	
}

void init()
{
	drawInput();
	wmove(w_in,1,1);
	if(sensor.Initialize())
	{
		waddstr(w_in,"Initialize Sent");
	}
	else
	{
		waddstr(w_in,"Initialize Failed");
	}
	wrefresh(w_in);
}

void reset()
{
	drawInput();
	wmove(w_in,1,1);
	if(sensor.Reset())
	{
		waddstr(w_in,"Reset Sent");
	}
	else
	{
		waddstr(w_in,"Reset Failed");
	}
	wrefresh(w_in);	
}

void selftest()
{
	drawInput();
	wmove(w_in,1,1);
	if(sensor.SelfTest())
	{
		waddstr(w_in,"Self Test Sent");
	}
	else
	{
		waddstr(w_in,"Self Test Failed");
	}
	wrefresh(w_in);
}

void data()
{
	unsigned char msg_id;
	unsigned char interface_id;
	
	drawInput();
	wmove(w_in,1,1);
	waddstr(w_in,"Interface id: ");
	echo();
	wscanw(w_in,"%hhd",&interface_id);
	noecho();
	wmove(w_in,2,1);
	waddstr(w_in,"Message id: ");
	echo();
	wscanw(w_in,"%hhd",&msg_id);
	noecho();
	wmove(w_in,3,1);
	if(sensor.ReqData(interface_id,msg_id))
	{
		wprintw(w_in,"Data Requested (%hhd)",msg_id);
	}
	else
	{
		waddstr(w_in,"Data Request Failed");
	}
	wrefresh(w_in);
	
}

void stream()
{
	unsigned char msg_id;
	unsigned long count;
	unsigned char interface_id;

	drawInput();
	wmove(w_in,1,1);
	waddstr(w_in,"Interface id: ");
	echo();
	wscanw(w_in,"%hhd",&interface_id);
	noecho();
	wmove(w_in,2,1);
	waddstr(w_in,"Message id: ");
	echo();
	wscanw(w_in,"%hhd",&msg_id);
	noecho();
	wmove(w_in,3,1);
	waddstr(w_in,"Message count: ");
	echo();
	wscanw(w_in,"%ld",&count);
	noecho();
	wmove(w_in,4,1);
	if(sensor.ReqStream(interface_id,msg_id,count))
	{
		wprintw(w_in,"Data Requested (%hhd)",msg_id);
	}
	else
	{
		waddstr(w_in,"Stream Request Failed");
	}
	wrefresh(w_in);
}

void poweron()
{	
	drawInput();
	wmove(w_in,1,1);	
	if(sensor.PowerOn())
	{
		waddstr(w_in,"Power On Sent");
	}
	else
	{
		waddstr(w_in,"Power On Failed");
	}
	wrefresh(w_in);
}

void powerdown()
{
	drawInput();
	wmove(w_in,1,1);
	if(sensor.PowerDown())
	{
		waddstr(w_in,"Power Down Sent");
	}
	else
	{
		waddstr(w_in,"Power Down Failed");
	}
	wrefresh(w_in);
}

void version()
{
	drawInput();
	wmove(w_in,1,1);
	if(sensor.ReqVersion())
	{
		waddstr(w_in,"Version Request Sent");
	}
	else
	{
		waddstr(w_in,"Version Request Failed");
	}
	wrefresh(w_in);
}

void asim_command()
{
	unsigned char cmd_id;
	short length;
	unsigned char* data;
	int i;
	unsigned char interface_id;

	drawInput();
	wmove(w_in,1,1);
	waddstr(w_in,"Interface id: ");
	echo();
	wscanw(w_in,"%hhd",&interface_id);
	noecho();
	wmove(w_in,2,1);
	waddstr(w_in,"Command id: ");
	echo();
	wscanw(w_in,"%hhd",&cmd_id);
	noecho();
	wmove(w_in,3,1);
	waddstr(w_in,"Command length: ");
	echo();
	wscanw(w_in,"%hd",&length);
	noecho();
	data = (unsigned char*)malloc(sizeof(unsigned char)*length);
	for(i=0;i<length;i++)
	{
		wmove(w_in,4+i,1);
		waddstr(w_in,"Command byte: ");
		echo();
		wscanw(w_in,"%hhd",&(data[i]));
		noecho();
	}
	wmove(w_in,5+i,1);
	if(sensor.Command(interface_id,cmd_id,length,data))
	{
		wprintw(w_in,"Command %hhd Sent",cmd_id);
	}
	else
	{
		wprintw(w_in,"Command %hhd Failed",cmd_id);
	}
	free(data);
	wrefresh(w_in);
}

void xteds()
{
	drawInput();
	wmove(w_in,1,1);
	if(sensor.ReqxTEDS())
	{
		waddstr(w_in,"xTEDS Request Sent");
	}
	else
	{
		waddstr(w_in,"xTEDS Request Failed");
	}
	wrefresh(w_in);
}

void timeattone()
{
	long sec,usec;

	drawInput();
	wmove(w_in,1,1);
	waddstr(w_in,"seconds: ");
	echo();
	wscanw(w_in,"%ld",&sec);
	noecho();
	wmove(w_in,2,1);
	waddstr(w_in,"microsecons: ");
	echo();
	wscanw(w_in,"%ld",&usec);
	noecho();
	wmove(w_in,3,1);
	wprintw(w_in,"Time at Tone:");
	wmove(w_in,4,1);
	wprintw(w_in,"%ld s %ld us",sec,usec);	
	wmove(w_in,5,1);
	if(sensor.TimeAtTone(sec,usec))
	{
		waddstr(w_in,"Time at Tone Sent");
	}
	else
	{
		waddstr(w_in,"Time at Tone Failed");
	}
	wrefresh(w_in);	
}

void cancel()
{
	unsigned char msg_id;
unsigned char interface_id;

	drawInput();
	wmove(w_in,1,1);
	waddstr(w_in,"Interface id: ");
	echo();
	wscanw(w_in,"%hhd",&interface_id);
	noecho();
	wmove(w_in,2,1);
	waddstr(w_in,"Message id: ");
	echo();
	wscanw(w_in,"%hhd",&msg_id);
	noecho();
	wmove(w_in,3,1);
	wprintw(w_in,"Data Canceled (%hhd)",msg_id);
	wmove(w_in,4,1);
	if(sensor.Cancel(interface_id,msg_id))
	{		
		waddstr(w_in,"Cancel Sent");
	}
	else
	{
		waddstr(w_in,"Cancel Failed");
	}
	wrefresh(w_in);
}
