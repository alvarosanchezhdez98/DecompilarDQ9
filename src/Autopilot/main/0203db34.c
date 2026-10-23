#include <m2c.h>


void func_0203db24(void *arg0, s32 arg1) {
    s32 *temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 **, 0x14);
    if (temp_r0 != NULL) {
        *temp_r0 = arg1;
    }
}
