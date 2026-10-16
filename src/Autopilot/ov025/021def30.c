#include <m2c.h>


void func_ov025_021def30(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0x770A) == 0) {
        M2C_FIELD(arg0, s32 *, 0x55D8) = (s32) (M2C_FIELD(arg0, s32 *, 0x55D8) + 1);
    }
    M2C_FIELD(arg0, s32 *, 0xEAC) = 1;
    M2C_FIELD(arg0, s32 *, 0x770C) = 0;
}
