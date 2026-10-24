#include <m2c.h>

void *func_0205d81c(s32);

void func_ov002_02157030(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3, s16 *arg4, s16 *arg5) {
    void *temp_r0;

    temp_r0 = func_0205d81c(arg0 + 0xEC8);
    if (temp_r0 == NULL) {
        return;
    }
    *arg2 = M2C_FIELD(temp_r0, s16 *, 0xAC);
    *arg3 = M2C_FIELD(temp_r0, s16 *, 0xAE);
    *arg4 = M2C_FIELD(temp_r0, s16 *, 0xA8);
    *arg5 = M2C_FIELD(temp_r0, s16 *, 0xAA);
}
