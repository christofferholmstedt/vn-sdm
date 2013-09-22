#ifndef __SDM_DEBUG_H_
#define __SDM_DEBUG_H_

// A macro for debug output, which can be conditionally removed, the variable "debug"
// must be defined at global scope, as in the DM, TM, SM, and PM.  Called debug_f because
// all params beyond "Level" are passed to printf.
#ifndef REMOVE_DEBUG_OUTPUT
#  ifndef debug_f
#  define debug_f(Level,...)  do { if (Level<=debug) { printf(__VA_ARGS__); } } while(0)
#  endif
#else
#  define debug_f(Level,...)
#endif

#endif //#ifndef __SDM_DEBUG_H_
