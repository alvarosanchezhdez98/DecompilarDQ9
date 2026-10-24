#include <m2c.h>


void func_ov000_02174a38(void *arg0, s32 arg1) {
    u8 temp_r1;
    s32 var_r1;

    temp_r1 = M2C_FIELD(arg0, u8 *, 0x24);
    if (arg1 != 0) {
        var_r1 = temp_r1 | 4;
    } else {
        var_r1 = temp_r1 & ~4;
    }
    M2C_FIELD(arg0, u8 *, 0x24) = var_r1;
}
