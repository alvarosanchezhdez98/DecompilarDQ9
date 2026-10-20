#include <m2c.h>

M2C_UNK func_020b20b0(s32, u8, u8, M2C_UNK, s32, s32, s32, s32);
s32 ov13_0223FDE0(M2C_UNK, M2C_UNK);
M2C_UNK ov13_0223FDF4(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_0223FE98(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02240008(M2C_UNK, M2C_UNK, s32);

void ov13_02240D94(void *arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3, s32 arg4) {
    s32 temp_r5;

    temp_r5 = ov13_0223FDE0(arg3, 0);
    ov13_0223FDF4(arg3, -1, 0, 0);
    ov13_0223FE98(arg3, -1, 0, 0xF);
    ov13_02240008(arg3, -1, arg4);
    func_020b20b0(temp_r5, M2C_FIELD(arg0, u8 *, 0x2E), M2C_FIELD(arg0, u8 *, 0x2F), arg1, arg2, 0, (s32) M2C_FIELD(arg0, u16 *, 0x2C), 2);
}
