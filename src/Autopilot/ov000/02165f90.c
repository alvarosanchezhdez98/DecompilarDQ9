#include <m2c.h>


void func_ov000_02165f90(void *arg0, void *arg1) {
    s32 var_r3;
    s32 var_r3_2;
    u8 *var_ip;
    u8 *var_ip_2;
    u8 *var_lr;
    u8 *var_lr_2;
    u8 temp_r2;
    u8 temp_r2_2;

    var_lr = arg1 + 2;
    var_ip = arg0 + 2;
    M2C_FIELD(arg0, u16 *, 0) = (u16) M2C_FIELD(arg1, u16 *, 0);
    var_r3 = 8;
    do {
        temp_r2 = *var_lr;
        var_lr += 1;
        var_r3 -= 1;
        *var_ip = temp_r2;
        var_ip += 1;
    } while (var_r3 != 0);
    var_lr_2 = arg1 + 0xD;
    var_ip_2 = arg0 + 0xD;
    M2C_FIELD(arg0, u8 *, 0xA) = (u8) M2C_FIELD(arg1, u8 *, 0xA);
    var_r3_2 = 8;
    M2C_FIELD(arg0, u8 *, 0xB) = (u8) M2C_FIELD(arg1, u8 *, 0xB);
    M2C_FIELD(arg0, u8 *, 0xC) = (u8) M2C_FIELD(arg1, u8 *, 0xC);
    do {
        temp_r2_2 = *var_lr_2;
        var_lr_2 += 1;
        var_r3_2 -= 1;
        *var_ip_2 = temp_r2_2;
        var_ip_2 += 1;
    } while (var_r3_2 != 0);
    M2C_FIELD(arg0, u8 *, 0x15) = (u8) M2C_FIELD(arg1, u8 *, 0x15);
    M2C_FIELD(arg0, u8 *, 0x16) = (u8) M2C_FIELD(arg1, u8 *, 0x16);
    M2C_FIELD(arg0, u8 *, 0x17) = (u8) M2C_FIELD(arg1, u8 *, 0x17);
}
