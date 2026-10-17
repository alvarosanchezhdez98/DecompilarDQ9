#include <m2c.h>


void func_ov017_02199998(s32 arg0) {
    *(u16 *)0x0400000A = (*(u16 *)0x0400000A & ~3) | arg0;
}
