#include <m2c.h>

s32 *func_0207f6ac(s32);

void func_02080fc4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *temp_r0;

    temp_r0 = func_0207f6ac(arg0 + 4);
    if (temp_r0 != NULL) {
        *temp_r0 = arg2;
    }
}
