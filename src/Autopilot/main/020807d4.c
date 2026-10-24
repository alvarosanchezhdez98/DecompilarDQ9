#include <m2c.h>

void *func_0207f0ac(s32);

void func_020807c4(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3) {
    void *temp_r0;

    temp_r0 = func_0207f0ac(arg0 + 0xC);
    if (temp_r0 == NULL) {
        return;
    }
    *arg2 = M2C_FIELD(temp_r0, s16 *, 0xA) * 8;
    *arg3 = M2C_FIELD(temp_r0, s16 *, 0xC) * 8;
}
