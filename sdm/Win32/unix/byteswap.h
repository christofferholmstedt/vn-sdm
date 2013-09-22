#ifndef __byteswap_h_
#define __byteswap_h_

#define bswap_32(x) ( ((0x000000FF&x) << 24) | ((0x0000FF00&x) << 8) | ((0x00FF0000&x) >> 8) | ((0xFF000000&x) >> 24) )


#endif // __byteswap_h_

