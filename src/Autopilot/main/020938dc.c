#include <m2c.h>


s32 func_020938cc(void) {
    if (((s32) (*(u16 *)0x04000304 & 0x8000) >> 0xF) != 1) {
        return 1;
    }
    return 0;
}
