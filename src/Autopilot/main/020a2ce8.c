#include <m2c.h>


void func_020a2cd8(void *arg0, s32 arg1) {
    u8 temp_r1;
    s32 var_r1;

    temp_r1 = M2C_FIELD(arg0, u8 *, 0x245);
    if (arg1 != 0) {
        var_r1 = temp_r1 | 2;
    } else {
        var_r1 = temp_r1 & ~2;
    }
    M2C_FIELD(arg0, u8 *, 0x245) = var_r1;
}
