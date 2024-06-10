#include "bswap.h"

uint16_t __builtin_bswap16(uint16_t byte_16)
{
    uint16_t l_byte = byte_16 & 0x00ff;
    byte_16 >>= 8;
    byte_16 |= (l_byte << 8);
    return byte_16;
}
uint32_t __builtin_bswap32(uint32_t byte_32)
{
    uint32_t l_byte = byte_32 & 0x0000ffff;
    byte_32 >>= 16;
    byte_32 |= (l_byte << 16);
    return byte_32;
}
