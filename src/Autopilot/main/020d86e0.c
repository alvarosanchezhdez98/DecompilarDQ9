#include <m2c.h>

extern u8 data_0214e4a0;

void func_020d86d0(s32 arg0, s32 arg1) {
    u8 var_r1;

    *(s32 *)0x04000540 = arg0 | (arg1 * 2);
    if (data_0214e4a0 == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    data_0214e4a0 = var_r1;
}
