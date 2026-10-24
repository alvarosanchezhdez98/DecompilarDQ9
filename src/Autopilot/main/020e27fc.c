#include <m2c.h>

void *func_0205a3d0();

void func_020e27ec(s32 arg0, s32 arg1, s16 arg2, s16 arg3) {
    void *temp_r0;

    temp_r0 = func_0205a3d0();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s16 *, 4) = arg2;
        M2C_FIELD(temp_r0, s16 *, 6) = arg3;
    }
}
