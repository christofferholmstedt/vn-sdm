#ifndef _SDM_TASK_DEFS_H_
#define _SDM_TASK_DEFS_H_

#define NUMTASKS	50					// for pm
#define PID_INVALID	0

// task status
#define INACTIVE		0
#define ACTIVE			1
#define ASSIGNED		2
#define SCHEDULED		3		// Assigned to a PM
#define PENDING			4		// Waiting to be scheduled
#define FINISHED		5		// Task state is finished running
#define RUNNING                 6               // Task is running

// task modes
#define MODE_NORMAL             0
#define MODE_ALWAYS_RUNNING     1

// resource definitions
#define SDM_SPAU	0x0001			// first nibble: arch
#define SDM_INTEL	0x0002
#define SDM_PPC_7404	0x0004
#define SDM_PPC_755	0x0005
#define SDM_PPC_405	0x0006
#define SDM_MICROBLAZE	0x0007
#define SDM_SPARC	0x0008

#define SDM_MEM32	0x0010			// second nibble: mem
#define SDM_MEM64	0x0020
#define SDM_MEM128	0x0030
#define SDM_MEM256	0x0040
#define SDM_MEM512  0x0050
#define SDM_MEM1024	0x0060

#define SDM_LINUX24	0x0100			// third nibble: OS
#define SDM_LINUX26	0x0200
#define SDM_WIN32	0x0300
#define SDM_VXWORKS	0x0400

#define ARCHMASK	0x000F			// architecture mask for resources
#define MEMMASK		0x00F0			// memory mask
#define OSMASK		0x0F00			// OS mask
#define PMIDMASK	0xF000			// PM node id mask

// Used for specifying a pm node id in the resource requirements
// to be used in position a in 0xa000, must be between 1 and 255
#define PM_ID(value)	(value << 12)

// operating mode definitions
#define NORMAL_MODE	1
#define QUIET_MODE	2
#define SPECIAL_MODE	3
#define CRITICAL_MODE	4

#endif
