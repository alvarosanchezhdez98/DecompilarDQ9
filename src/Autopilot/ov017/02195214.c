#include <m2c.h>
#pragma optimize_for_size off


void func_ov017_02195214(void *arg0, void *arg1) {
    s32 var_r3;
    u8 *var_ip;
    u8 *var_lr;
    u8 temp_r2;

    var_lr = arg1 + 2;
    var_ip = arg0 + 2;
    M2C_FIELD(arg0, u8 *, 0) = (u8) M2C_FIELD(arg1, u8 *, 0);
    var_r3 = 0xC;
    M2C_FIELD(arg0, u8 *, 1) = (u8) M2C_FIELD(arg1, u8 *, 1);
    do {
        temp_r2 = *var_lr;
        var_lr += 1;
        var_r3 -= 1;
        *var_ip = temp_r2;
        var_ip += 1;
    } while (var_r3 != 0);
    M2C_FIELD(arg0, u8 *, 0xE) = (u8) M2C_FIELD(arg1, u8 *, 0xE);
}
