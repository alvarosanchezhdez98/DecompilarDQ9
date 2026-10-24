#include <m2c.h>

void *func_0209bd94();

void func_0209be28(s32 arg0, s32 arg1, s32 *arg2) {
    void *temp_r0;

    temp_r0 = func_0209bd94();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s32 *, 4) = (s32) *arg2;
    }
}
