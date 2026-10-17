#include <m2c.h>

void *func_020421a0();

void func_ov003_02160b2c(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x464) & 0x20000) {
        return;
    }
    M2C_FIELD(func_020421a0(), s8 *, 0x19AE) = 0;
}
