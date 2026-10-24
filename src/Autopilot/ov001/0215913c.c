#include <m2c.h>
#pragma optimization_level 4

void *func_ov001_02158e0c();

void func_ov001_0215913c(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_r0;

    temp_r0 = func_ov001_02158e0c();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 0) = 0xD;
        M2C_FIELD(temp_r0, s32 *, 4) = arg1;
        M2C_FIELD(temp_r0, s32 *, 8) = arg2;
        M2C_FIELD(temp_r0, s32 *, 0xC) = arg3;
    }
}
