#include <m2c.h>


void func_02093b54(u8 *arg0, u8 *arg1) {
    s32 var_r3;
    u8 *var_ip;
    u8 *var_lr;
    u8 temp_r2;

    var_lr = arg1;
    var_ip = arg0;
    var_r3 = 0x30;
    do {
        temp_r2 = *var_lr;
        var_lr += 1;
        var_r3 -= 1;
        *var_ip = temp_r2;
        var_ip += 1;
    } while (var_r3 != 0);
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) M2C_FIELD(arg1, s16 *, 0x30);
    M2C_FIELD(arg0, s8 *, 0x32) = (s8) M2C_FIELD(arg1, s8 *, 0x32);
    M2C_FIELD(arg0, u8 *, 0x33) = (u8) M2C_FIELD(arg1, u8 *, 0x33);
}
