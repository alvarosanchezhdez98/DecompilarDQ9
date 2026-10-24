#include <m2c.h>

void *func_0204673c();

void *func_020467c0(s32 arg0, s32 arg1, s32 *arg2) {
    void *temp_r0;

    temp_r0 = func_0204673c();
    if (temp_r0 == NULL) {
        return NULL;
    }
    if (arg2 != NULL) {
        *arg2 = M2C_FIELD(temp_r0, s32 *, 0x44);
    }
    return temp_r0 + M2C_FIELD(temp_r0, s32 *, 0x40);
}
