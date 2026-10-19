#include <m2c.h>


void func_020e2b78(s32 arg0) {
    *(s32 *)0x04001000 = (*(s32 *)0x04001000 & ~0xE000) | (arg0 << 0xD);
}
