#include <m2c.h>
#pragma optimization_level 4


void func_ov017_02199964(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *(u16 *)0x0400000A = (*(u16 *)0x0400000A & 0x43) | (arg0 << 0xE) | (arg1 << 7) | (arg2 << 8) | (arg3 * 4) | (arg4 << 0xD);
}
