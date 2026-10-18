#include <m2c.h>


void func_020e2b94(s32 arg0) {
    *(s32 *)0x04000000 = (*(s32 *)0x04000000 & ~0xE000) | (arg0 << 0xD);
}
