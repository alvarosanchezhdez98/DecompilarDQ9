#include <m2c.h>


void func_ov017_021999e0(s32 arg0) {
    *(u16 *)0x0400000C = (*(u16 *)0x0400000C & ~3) | arg0;
}
