#include <m2c.h>

void *func_0205a3d0();

void func_0205a42c(s32 arg0, s32 arg1, s8 arg2) {
    void *temp_r0;

    temp_r0 = func_0205a3d0();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s8 *, 0x14) = arg2;
    }
}
