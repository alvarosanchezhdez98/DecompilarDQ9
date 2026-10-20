#include <m2c.h>

s16 func_020d1cc8(s32, s32, M2C_UNK);
M2C_UNK func_ov031_0221b780(s32, M2C_UNK, s32);
s32 func_ov031_0221b848();
s32 verify(s32, s32, M2C_UNK, s32);
extern M2C_UNK data_ov031_0224e6a0;

s32 DWCi_BACKUPlWriteAll(s32 arg0) {
    s32 var_r5;
    s32 var_r6;
    s32 var_r7;

    var_r6 = M2C_FIELD(&data_ov031_0224e6a0, s32 *, 8);
    var_r7 = arg0;
    var_r5 = 0;
    do {
        M2C_FIELD((arg0 + (var_r5 << 8)), s16 *, 0xFE) = func_020d1cc8(arg0 + 0x500, var_r7, 0xFE);
loop_2:
        func_ov031_0221b780(var_r6, 0x100, var_r7);
        if (verify(var_r7, var_r6, 0x100, arg0 + 0x400) == 0) {
            goto loop_2;
        }
        var_r5 += 1;
        var_r7 += 0x100;
        var_r6 += 0x100;
    } while (var_r5 < 4);
    if (func_ov031_0221b848() != 0) {
        return 1;
    }
    return 0;
}
