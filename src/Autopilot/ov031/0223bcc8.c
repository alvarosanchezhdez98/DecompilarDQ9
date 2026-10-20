#include <m2c.h>


void ov13_02240008(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_ip;
    s32 var_lr;
    u16 temp_r1_2;
    void *temp_r1;
    void *temp_r3;

    temp_ip = M2C_FIELD(arg0, s32 *, 8);
    if (arg1 >= 0) {
        temp_r1 = temp_ip + (arg1 * 8);
        M2C_FIELD(temp_r1, u16 *, 4) = (u16) ((M2C_FIELD(temp_r1, u16 *, 4) & ~0xC00) | (arg2 << 0xA));
        return;
    }
    var_lr = 0;
    if ((s32) M2C_FIELD(arg0, u8 *, 0xC) <= 0) {
        return;
    }
    do {
        temp_r3 = temp_ip + (var_lr * 8);
        temp_r1_2 = M2C_FIELD(temp_r3, u16 *, 4);
        var_lr += 1;
        M2C_FIELD(temp_r3, s16 *, 4) = (s16) ((temp_r1_2 & ~0xC00) | (arg2 << 0xA));
    } while (var_lr < (s32) M2C_FIELD(arg0, u8 *, 0xC));
}
