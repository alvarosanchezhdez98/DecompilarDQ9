#include <m2c.h>

M2C_UNK _Z15CleanCacheRangePKvj(s32, s32);
M2C_UNK func_020d1ee4(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_020d1f70(M2C_UNK, s32, s32, M2C_UNK *, s32);
M2C_UNK func_020d1fb0(M2C_UNK, M2C_UNK);
M2C_UNK func_020d2038(M2C_UNK, M2C_UNK, s32, M2C_UNK, s32, u32, s32, s32, u32, s32);
M2C_UNK func_020d24c4(M2C_UNK);
extern M2C_UNK data_ov016_0219d0c0;
extern M2C_UNK func_ov016_0218bcc4;

void func_ov016_0218bce8(u32 arg0, u32 arg1) {
    s32 temp_r5;
    u32 temp_r0;

    temp_r0 = 0xFFB0FFU / arg0;
    temp_r5 = (arg1 >> 6) * (temp_r0 * 2);
    _Z15CleanCacheRangePKvj(M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x30), M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x24) * arg1 * 2);
    _Z15CleanCacheRangePKvj(M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x2C), M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x24) * arg1 * 2);
    func_020d1fb0(3, 0);
    func_020d2038(0, 1, M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x30), 1, 0, (u32) (M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x24) * arg1) >> 1, 0x7F, 0, temp_r0, 0);
    func_020d2038(1, 1, M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x2C), 1, 0, (u32) (M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x24) * arg1) >> 1, 0x7F, 0, temp_r0, 0x7F);
    func_020d1f70(0, temp_r5, temp_r5, &func_ov016_0218bcc4, 0);
    func_020d1ee4(3, 0, 1, 0);
    func_020d24c4(1);
}
