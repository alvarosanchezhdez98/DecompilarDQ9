#include <m2c.h>

M2C_UNK _Z17CallMenuObjectVf0P10MenuScriptti(M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_ov004_02156e2c(M2C_UNK, M2C_UNK);
s32 func_ov004_021570a4(M2C_UNK, u8);
M2C_UNK func_ov004_02159384(M2C_UNK);
extern M2C_UNK data_ov004_021707d8;

s32 func_ov004_021599b4(M2C_UNK arg0) {
    s32 temp_r0;
    u8 temp_r0_2;

    temp_r0 = func_ov004_02156e2c(arg0, 0x5B);
    if (temp_r0 < 0) {
        return 0;
    }
    if (func_ov004_021570a4(arg0, (u8) temp_r0) == 0) {
        return 0;
    }
    temp_r0_2 = M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), u8 *, 0x11);
    if ((u32) temp_r0_2 <= 1U) {
        return 0;
    }
    M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), u8 *, 0x11) = (u8) (temp_r0_2 - 1);
    _Z17CallMenuObjectVf0P10MenuScriptti(arg0, 0x25C, 1);
    func_ov004_02159384(arg0);
    return 0;
}
