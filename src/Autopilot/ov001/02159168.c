#include <m2c.h>

void *func_ov001_02158e0c();

void func_ov001_02159168(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    void *temp_r0;

    temp_r0 = func_ov001_02158e0c();
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s32 *, 0) = 0xE;
    M2C_FIELD(temp_r0, s32 *, 4) = arg1;
    M2C_FIELD(temp_r0, s32 *, 8) = arg2;
    M2C_FIELD(temp_r0, s32 *, 0xC) = arg3;
    M2C_FIELD(temp_r0, s32 *, 0x1C) = arg4;
    M2C_FIELD(temp_r0, s32 *, 0x20) = arg5;
    M2C_FIELD(temp_r0, s32 *, 0x24) = (s32) arg6;
}
