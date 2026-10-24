#include <m2c.h>
#pragma optimization_level 4

void *func_ov001_02158e0c();

void func_ov001_021590fc(s32 arg0, s32 arg1) {
    void *temp_r0;

    temp_r0 = func_ov001_02158e0c();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 0) = 0xB;
        M2C_FIELD(temp_r0, s32 *, 0x1C) = arg1;
    }
}
