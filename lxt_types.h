#ifndef _LXT_TYPES_H
#define _LXT_TYPES_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif

#ifndef false
#define false    0
#endif

#ifndef true
#define true     1
#endif

#ifndef NULL
#define NULL    ((void *) 0)
#endif

typedef unsigned char bool_t;

typedef unsigned char uint8_t;
//typedef char int8_t;

typedef unsigned short uint16_t;
typedef short int16_t;

typedef unsigned int uint32_t;
typedef int int32_t;

typedef unsigned long long uint64_t;
typedef long long int64_t;

typedef float float_t;
typedef double double_t;

#define BIG_LIT_SWAP16(A)        ((((uint16_t)(A) & 0xff00) >> 8) | \
                                                       (((uint16_t)(A) & 0x00ff) << 8))

#define BIG_LIT_SWAP32(A)        ((((uint32_t)(A) & 0xff000000) >> 24) | \
                                                       (((uint32_t)(A) & 0x00ff0000) >> 8) | \
                                                       (((uint32_t)(A) & 0x0000ff00) << 8) | \
                                                       (((uint32_t)(A) & 0x000000ff) << 24))

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
