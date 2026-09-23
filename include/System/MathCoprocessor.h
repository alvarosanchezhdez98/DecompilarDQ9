#pragma once

#include "std_library_functions.h"

// The NitroSDK's CP: the hardware divider and square root unit, used by the fixed-point math (see Matrix.h)

// Only the control registers are volatile, like in the NitroSDK (REGType64 isn't, REGType64v is): the compiler can
// combine the accesses to the operands and results
#define REG_DIVCNT (*(volatile unsigned short*)0x04000280)
#define REG_DIV_NUMER (*(uint64_t*)0x04000290)
#define REG_DIV_NUMER_32 (*(uint32_t*)0x04000290)
#define REG_DIV_DENOM (*(uint64_t*)0x04000298)
#define REG_DIV_RESULT (*(uint64_t*)0x040002a0)
#define REG_DIV_RESULT_32 (*(uint32_t*)0x040002a0)
#define REG_DIVREM_RESULT_32 (*(uint32_t*)0x040002a8)
#define REG_SQRTCNT (*(volatile unsigned short*)0x040002b0)
#define REG_SQRT_RESULT (*(uint32_t*)0x040002b4)
#define REG_SQRT_PARAM (*(uint64_t*)0x040002b8)

#define DIVCNT_MODE_32_32 0
#define DIVCNT_MODE_64_32 1
#define DIVCNT_MODE_64_64 2
#define DIVCNT_BUSY 0x8000
#define SQRTCNT_MODE_32 0
#define SQRTCNT_MODE_64 1
#define SQRTCNT_BUSY 0x8000

// The NitroSDK's CP_SetDiv32_32, CP_SetDiv64_32 and CP_SetDiv64_64: start a division
static inline void StartDivision32_32(unsigned long numerator, unsigned long denominator)
{
    REG_DIVCNT = DIVCNT_MODE_32_32;
    REG_DIV_NUMER_32 = numerator;
    REG_DIV_DENOM = denominator;
}

static inline void StartDivision64_32(uint64_t numerator, unsigned long denominator)
{
    REG_DIVCNT = DIVCNT_MODE_64_32;
    REG_DIV_NUMER = numerator;
    REG_DIV_DENOM = denominator;
}

static inline void StartDivision64_64(uint64_t numerator, uint64_t denominator)
{
    REG_DIVCNT = DIVCNT_MODE_64_64;
    REG_DIV_NUMER = numerator;
    REG_DIV_DENOM = denominator;
}

// The NitroSDK's CP_SetDivImm64_32: starts a division without setting the mode, which the previous division set
static inline void StartDivision64_32SameMode(uint64_t numerator, unsigned long denominator)
{
    REG_DIV_NUMER = numerator;
    REG_DIV_DENOM = denominator;
}

// The NitroSDK's CP_SetSqrt64: starts a square root
static inline void StartSquareRoot64(uint64_t value)
{
    REG_SQRTCNT = SQRTCNT_MODE_64;
    REG_SQRT_PARAM = value;
}

// The NitroSDK's CP_GetDivResult64, CP_GetDivResult32 and CP_GetDivRemainder32: wait for the division
static inline int64_t GetDivisionResult64()
{
    while (REG_DIVCNT & DIVCNT_BUSY)
    {
    }
    return (int64_t)REG_DIV_RESULT;
}

static inline long GetDivisionResult32()
{
    while (REG_DIVCNT & DIVCNT_BUSY)
    {
    }
    return (long)REG_DIV_RESULT_32;
}

static inline long GetDivisionRemainder32()
{
    while (REG_DIVCNT & DIVCNT_BUSY)
    {
    }
    return (long)REG_DIVREM_RESULT_32;
}

// The NitroSDK's CP_GetSqrtResult32: waits for the square root
static inline unsigned long GetSquareRootResult32()
{
    while (REG_SQRTCNT & SQRTCNT_BUSY)
    {
    }
    return (unsigned long)REG_SQRT_RESULT;
}
