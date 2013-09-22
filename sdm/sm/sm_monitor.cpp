/**
 * Sensor Manager monitor - main program unit
 *
 * The Sensor Manager monitor starts the Sensor Manager (SM) process, and
 * ensures that it is up and responding.  The monitor periodically sends a
 * heartbeat message to the SM. If this monitor detects no or improper response
 * from the SM, the SM process will be restarted.  This provides a level of
 * robustness for the SM.
 *
 * See sm.cpp for reference information on the command line arguments, which
 * are passed through from this Sensor Manager monitor to the Sensor Manager
 * process.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <string.h>
#include "../common/message/SDMReady.h"
#include "../common/MessageManager/MessageManager.h"
#include "../common/TCPcom.h"

#define NUM_HEARTBEAT_TRIES	2	//Number of times to miss a response before restarting the SM

pid_t StartSM(char **);   // Starts the Sensor Manager process
void SigIntHandler(int);  // The non-default signal handler for SIGINT

pid_t sm_pid = -1;		//Process id number of the Sensor Manager


/**
 * main - entry point for SM monitor process
 *
 * @param argc - the argument count
 * @param argv - the command arguments
 *
 * @return >= 0 for no error, < 0 for error
 */
int main(int argc, char ** argv)
{
	int result = -1;      // set with Termination status for child process
  int miss_count = 0;	// Count of number of heartbeat messages missed
  int num_toget = 0;	// The number of messages to receive per
                                // heartbeat
  char buf[BUFSIZE];	// Buffer for message receipt
  SDMReady heartbeat;	// Heart-beat message instance
  MessageManager mm;	// Message manager helper instance
  SDMComponent_ID sm;	// ID information on Sensor Manager process

  const size_t max_proc_size = 128;	// Limit the process name size to
                                        // reasonable length
  size_t prog_size = 0;		// The size to build the process name
  size_t argv0_size = 0;	// The length of argv[0]
  size_t suffix_size = 0;	// The length of the suffix to append to argv[0]
  char *proc_name = 0;		// The buffer pointer for building process-name
  const char* proc_suffix = "_process";	// Suffix to add to the incoming
                                        // process name

  const char* localhostIp = "127.0.0.1"; // The standard local host IP address

  /////////////////////////////////////////////////////////////////////////////
  // Set up the command line for the child process
  // Prepares a new argv[0] for SM with name of <this_process>_process
  /////////////////////////////////////////////////////////////////////////////
  argv0_size  = strlen(argv[0]);
  if (argv0_size > max_proc_size)
  {
    printf("  Monitor: Command path too long for SM.\n");
    return(-1);
  }

  suffix_size = strlen(proc_suffix);

  // Allocate for full size, including terminator and for the '_process' suffix,
  // but limit the length to reasonable length
  if(argv0_size + suffix_size + 1 < max_proc_size)
  {
    prog_size = argv0_size + suffix_size + 1;
  }
  else
  {
    prog_size = max_proc_size;
  }

  try
  {
    proc_name = new char[prog_size];
  }
  catch(...)
  {
    printf("  Monitor:  Error allocating %u bytes for command name.\n",
	   prog_size);
    return(-1);
  }

  // set a size to ensure to leave enough space in buffer for suffix to be
  // appended
  size_t max_argv_chars;
  if(max_proc_size - (suffix_size + 1) < argv0_size)
  {
      max_argv_chars = max_proc_size - (suffix_size + 1);
  }
  else
  {
      max_argv_chars = argv0_size;
  }
  strncpy(proc_name, argv[0], max_argv_chars);
  if ( max_argv_chars > 0 )
    proc_name[max_argv_chars] = '\0';	// ensure termination
  strcat(proc_name, proc_suffix);	// append the suffix

  /////////////////////////////////////////////////////////////////////////////
  // Process the command line arguments...
  // A copy of the argv's are prepared to pass along to the SM instance.  The
  // exception is that argv[0] is prepared as per above with a suffix.
  /////////////////////////////////////////////////////////////////////////////
  char **nargv = new char*[argc+1];
  nargv[0] = proc_name;
  for (int i = 1;  i < argc;  ++i)
    nargv[i] = argv[i];
  nargv[argc] = NULL;


  /////////////////////////////////////////////////////////////////////////////
  // Prepare for the heartbeat messaging...
  /////////////////////////////////////////////////////////////////////////////

  //Set monitor process address
  heartbeat.source.setSensorID(0);
  heartbeat.source.setAddress(inet_addr(localhostIp));
  heartbeat.source.setPort(PORT_SM_MONITOR);

  //Set SM address
  sm.setAddress(inet_addr(localhostIp));
  sm.setPort(PORT_SM);
  sm.setSensorID(0);

  // Setup a signal handler for SIGINT, the user-keyboard interrupt signal
  signal(SIGINT, SigIntHandler);


  /////////////////////////////////////////////////////////////////////////////
  // Start the SM in a seperate process
  /////////////////////////////////////////////////////////////////////////////

  sm_pid = StartSM(nargv);

  /////////////////////////////////////////////////////////////////////////////
  //
  /////////////////////////////////////////////////////////////////////////////

  mm.Async_Init_Both(PORT_SM+1);

  /////////////////////////////////////////////////////////////////////////////
  // Start the heartbeat monitoring...
  // If SM quits, or no messages received in allowed time frame, then restart
  // the SM
  /////////////////////////////////////////////////////////////////////////////

  //If fork/exec was successful
  if (sm_pid > 0)
  {
    //Allow the SM to get started up
    sleep(HEARTBEAT_INTERVAL);
    while (1)
    {

      //Send heartbeats via UDP and TCP
      heartbeat.SendTo(sm);
      heartbeat.Sendtcp(sm);
      sleep(HEARTBEAT_INTERVAL);

      //If Sensor Manager quit
      if (waitpid(-1,&result,WNOHANG) == sm_pid)
      {
			printf("  Monitor:  SM failed, restarting...\n");
			sm_pid = StartSM(nargv);
			if (sm_pid > 0)
			{
			  sleep(HEARTBEAT_INTERVAL);
			  continue;
			}
			else
			{
			  printf("  Monitor:  Could not restart the SM.\n");
			  return -1;
			}
      }
      else if (mm.IsReady())
      {
	//Should respond with two messages
	num_toget = 2;

	while (mm.IsReady())
	{
	  num_toget--;
	  mm.GetMessage(buf);
	}
	if (num_toget > 0)
	  miss_count++;
	else
	  miss_count = 0;
      }
      else
      {
	//If no messages were received
	miss_count++;
	if (miss_count == NUM_HEARTBEAT_TRIES)
	{
	  printf("  Monitor:  SM unresponsive, restarting...\n");

	  if (kill (sm_pid, SIGKILL) == 0)
	    wait(&result);
	  else
	    waitpid(-1, &result, WNOHANG);

	  sm_pid = StartSM(nargv);
	  if (sm_pid > 0)
	  {
	    sleep(HEARTBEAT_INTERVAL);
	    continue;
	  }
	  else
	  {
	    printf("  Monitor:  Could not restart the SM.\n");
	    return -1;
	  }
	}
      }
    }
  }
  else
  {
    printf("  Monitor:  Error starting the SM (%d).\n", sm_pid);
    // Cleanup allocations
    delete [] proc_name;
    return -1;
  }

  // Cleanup allocations
  delete [] proc_name;

  return 0;
}

/**
 * Start the Sensor Manager as a new process
 *
 * Post fork call, if this is the child process, the call to execvp(...) will
 * overlay this process, and hence replace exit from this function.
 *
 * @param argv - the argument list for sensor manager.
 * @return - the process ID of the Sensor Manager child process
 */
int StartSM(char ** argv)
{
	int pid;

	pid = fork();
	//Child Process
	if (pid == 0)
	{
		//Start the Sensor Manager
		if (execvp(argv[0],argv) < 0)
		{
			printf("  Monitor:  Error exec'ing the SM.\n");
			exit(-1);
		}
		//Here to make the compiler happy, never runs however
		return 0;
	}
	//Parent Process
	else
		return pid;
}

/**
 * Provides a handler for the SIGINT (Terminal Interrupt) signal
 *
 * @param sig_num - the argument list for sensor manager.
 *
 * @return - the process ID of the Sensor Manager child process
 *
 */
void SigIntHandler(int sig_num)
{
	int result = 0;
	if (kill (SIGINT, sm_pid) == 0)
		wait (&result);
	else
		waitpid(-1,&result,WNOHANG);

	exit(EXIT_SUCCESS);
}

