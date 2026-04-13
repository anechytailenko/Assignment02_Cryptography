#pragma once

#include "strumok_tables.h"

inline uint64_t strumok_T(uint64_t w)
{
    return strumok_T0[w & 0xFF] ^ strumok_T1[(w >> 8) & 0xFF] ^
           strumok_T2[(w >> 16) & 0xFF] ^ strumok_T3[(w >> 24) & 0xFF] ^
           strumok_T4[(w >> 32) & 0xFF] ^ strumok_T5[(w >> 40) & 0xFF] ^
           strumok_T6[(w >> 48)  & 0xFF] ^ strumok_T7[(w >> 56) & 0xFF];
}

inline uint64_t strumok_AlphaMul(uint64_t w)
{
    return (w << 8) ^ strumok_alpha_mul[w >> 56];
}

inline uint64_t strumok_AlphaInvMul(uint64_t w)
{
    return (w >> 8) ^ strumok_alphainv_mul[w & 0xFF];
}

inline uint64_t load64LittleEndian(const uint8_t* p) {
    return static_cast<uint64_t>(p[0]) |
          (static_cast<uint64_t>(p[1]) << 8) |
          (static_cast<uint64_t>(p[2]) << 16) |
          (static_cast<uint64_t>(p[3]) << 24) |
          (static_cast<uint64_t>(p[4]) << 32) |
          (static_cast<uint64_t>(p[5]) << 40) |
          (static_cast<uint64_t>(p[6]) << 48) |
          (static_cast<uint64_t>(p[7]) << 56);
}