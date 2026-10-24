#include <m2c.h>
#pragma optimization_level 4

void *func_ov001_02159f14();

void func_ov001_0215a3d8(s32 arg0, s32 arg1) {
    void *temp_r0;

    temp_r0 = func_ov001_02159f14();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 0) = 4;
        M2C_FIELD(temp_r0, s32 *, 0x10) = arg1;
    }
}
