#include <m2c.h>

void *func_0207f6ac(s32);

void func_02080828(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3) {
    void *temp_r0;

    temp_r0 = func_0207f6ac(arg0 + 4);
    if (temp_r0 != NULL) {
        *arg2 = M2C_FIELD(temp_r0, s16 *, 6);
        *arg3 = M2C_FIELD(temp_r0, s16 *, 8);
    }
}
