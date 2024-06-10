#ifndef __BSWAP_H
#define __BSWAP_H

//#include "headfile.h"

#include <stdint-gcc.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t __builtin_bswap16(uint16_t byte_16);
uint32_t __builtin_bswap32(uint32_t byte_32);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
