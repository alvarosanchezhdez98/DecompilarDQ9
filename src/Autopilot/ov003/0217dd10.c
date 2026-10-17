#include <m2c.h>

s32 func_020421a0();
M2C_UNK func_0204500c(s32, s32, M2C_UNK, M2C_UNK);
s32 func_020e0434(s32, s32);

void func_ov003_0217dd10(s32 arg0, s32 arg1) {
    s32 temp_r1;
    s32 var_r4;
    s32 var_r5;

    var_r4 = arg1;
    var_r5 = arg0;
    temp_r1 = var_r4 << 0x10;
    var_r4 = func_020421a0();
    func_0204500c(var_r4, func_020e0434(var_r5 + 0xCC, temp_r1 >> 0x10), 0, 0xE3);
    M2C_FIELD(var_r4, s8 *, 0x19B2) = 1;
    M2C_FIELD(var_r4, s32 *, 0x99C) = 2;
}
