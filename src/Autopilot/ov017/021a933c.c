#include <m2c.h>

void *func_020421a0();
M2C_UNK func_0204500c(void *, s32, M2C_UNK, M2C_UNK);
s32 func_020e0434(void *, s16);

void func_ov017_021a933c(void *arg0, s32 arg1) {
    s32 var_r5;
    void *temp_r4;

    var_r5 = arg1;
    temp_r4 = func_020421a0();
    if ((var_r5 <= 0xC7) && (var_r5 >= 0x64) && (M2C_FIELD(arg0, s32 *, 0x14) == 1)) {
        var_r5 += 0x64;
    }
    func_0204500c(temp_r4, func_020e0434(arg0 + 0x278, (s16) var_r5), 0, 0xE3);
    if ((var_r5 <= 0x12B) && (var_r5 >= 0x64)) {
        M2C_FIELD(temp_r4, s8 *, 0x19B2) = 1;
    } else {
        M2C_FIELD(temp_r4, s8 *, 0x19B2) = 0;
    }
    if (var_r5 > 0x12B) {
        return;
    }
    if (var_r5 < 0x64) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x14) == 0) {
        M2C_FIELD(temp_r4, s32 *, 0x99C) = 2;
        return;
    }
    M2C_FIELD(temp_r4, s32 *, 0x99C) = 1;
}
