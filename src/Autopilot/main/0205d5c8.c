#include <m2c.h>


void func_0205d5b8(void *arg0, s32 arg1) {
    u8 temp_r1;
    s32 var_r1;

    temp_r1 = M2C_FIELD(arg0, u8 *, 0xC5);
    if (arg1 != 0) {
        var_r1 = temp_r1 | 0x20;
    } else {
        var_r1 = temp_r1 & ~0x20;
    }
    M2C_FIELD(arg0, u8 *, 0xC5) = var_r1;
}
