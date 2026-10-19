#include <m2c.h>


void func_020a28b0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, u8 *, 0x244) = (u8) (M2C_FIELD(arg0, u8 *, 0x244) & ~arg1);
}
