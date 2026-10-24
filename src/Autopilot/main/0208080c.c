#include <m2c.h>

void *func_0207f0ac(s32);

void func_020807fc(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_r0;

    temp_r0 = func_0207f0ac(arg0 + 0xC);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, s16 *, 0xA) = (s16) (arg2 >> 3);
        M2C_FIELD(temp_r0, s16 *, 0xC) = (s16) (arg3 >> 3);
    }
}
