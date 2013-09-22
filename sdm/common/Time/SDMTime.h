#ifndef _SDM_TIME_H_
#define _SDM_TIME_H_

#ifdef WIN32
#  include "SDMTimeWin32.h"
#elif defined (RTEMS_BUILD)
#  include "SDMTimeRTEMS.h"
#else
#  include "SDMTimeLinux.h"
#endif

#endif
