#include <m2c.h>

void *func_ov017_0219c6f4();

void func_ov017_0219cd98(void *arg0) {
    void *temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x36BC) == 0) {
        return;
    }
    temp_r0 = func_ov017_0219c6f4();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s8 *, 2) = 1;
    }
}
