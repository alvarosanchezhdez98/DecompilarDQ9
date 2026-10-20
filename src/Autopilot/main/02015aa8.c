#include <m2c.h>


void func_02015a98(void *arg0, s8 arg1, s32 arg2, s32 arg3) {
    if (M2C_FIELD(arg0, u8 *, 0x16) == 1) {
        M2C_FIELD(arg0, u8 *, 0x16) = 2U;
        M2C_FIELD(arg0, s8 *, 0x14) = arg1;
        M2C_FIELD(arg0, s16 *, 0x10) = 0;
    } else if (arg3 != 0) {
        M2C_FIELD(arg0, u8 *, 0x16) = 2U;
        M2C_FIELD(arg0, s8 *, 0x14) = arg1;
        M2C_FIELD(arg0, s16 *, 0x10) = 0;
    }
    if (arg2 != 0) {
        M2C_FIELD(arg0, s8 *, 0x18) = 0;
    }
}
