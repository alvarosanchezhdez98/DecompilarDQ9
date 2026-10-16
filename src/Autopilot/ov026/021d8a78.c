#include <m2c.h>

void *func_020421a0();
M2C_UNK func_020dd0b0(M2C_UNK, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

s32 func_ov026_021d8a78(M2C_UNK arg0) {
    s32 temp_r4;

    temp_r4 = M2C_FIELD(func_020421a0(), s32 *, 0x5C);
    memset(temp_r4, 0, 0x960);
    func_020dd0b0(arg0, temp_r4);
    return temp_r4;
}
