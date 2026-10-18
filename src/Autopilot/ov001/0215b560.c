#include <m2c.h>

M2C_UNK func_ov001_0215b598(M2C_UNK);

s32 func_ov001_0215b560(void) {
    if (((s32) (*(u16 *)0x04000304 & 0x8000) >> 0xF) == 0) {
        func_ov001_0215b598(1);
    } else {
        func_ov001_0215b598(0);
    }
    return 1;
}
