#ifndef __byteswap_h_
#define __byteswap_h_

#define bswap_32(x) ( ((0x000000FF&x) << 24) | ((0x0000FF00&x) << 8) | ((0x00FF0000&x) >> 8) | ((0xFF000000&x) >> 24) )
#define bswap_16(x) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))
#define bswap_64(x) ((((x) & 0xff00000000000000ull) >> 56) \
| (((x) & 0x00ff000000000000ull) >> 40)     \
| (((x) & 0x0000ff0000000000ull) >> 24)     \
| (((x) & 0x000000ff00000000ull) >> 8)      \
| (((x) & 0x00000000ff000000ull) << 8)      \
| (((x) & 0x0000000000ff0000ull) << 24)     \
| (((x) & 0x000000000000ff00ull) << 40)     \
| (((x) & 0x00000000000000ffull) << 56))


#endif

