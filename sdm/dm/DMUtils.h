// Extra utility functions used by the Data Manager

#ifndef _SDM_DM_UTIL_H_
#define _SDM_DM_UTIL_H_

#define SdmImaDm   'd'
#define SdmImaTm   't'

#ifndef WIN32
#  include <net/if.h>
#  include <netdb.h>
#endif

#ifdef __uClinux__
#warning "Including SendIMA"
#define SEND_IMA
#include <netspwpnp/spwpnp.h>
struct spwpnp_ima {
  struct spwpnphdr          hdr;
  unsigned long             ip;
  unsigned short            port;
  unsigned char             csum;
} __attribute__((packed));

#endif

unsigned long GetNodeAddress(bool spacewire=false);

#ifdef SEND_IMA
int SendIMA(unsigned char which, int debug);
#endif

bool IsPIDFromASIM (long processID);
bool PIDToFileName (long processID, char fileName[]);
int Store_xTEDS (long processID, char* xTEDSIn);
int Retrieve_xTEDS (long processID, char* xTEDSOut);
void CreatexTEDSDirectory();

#endif //SDM_DM_UTILS

