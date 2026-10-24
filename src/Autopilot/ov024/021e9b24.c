#include <m2c.h>

M2C_UNK func_ov024_021da644(M2C_UNK, u32, u32);

void func_ov024_021e9b24(s32 arg0, M2C_UNK arg1, void *arg2, s32 arg3) {
    s32 temp_r2;

    if (arg3 != 0) {
        temp_r2 = M2C_FIELD(arg2, s32 *, 0x24);
        func_ov024_021da644(arg1, (u32) (temp_r2 << 0xC) >> 0x16, (u32) (temp_r2 * 4) >> 0x16);
        return;
    }
    func_ov024_021da644(arg1, (u32) (M2C_FIELD(arg2, s32 *, 0x20) * 4) >> 0x16, (u32) (M2C_FIELD(arg2, s32 *, 0x24) << 0x16) >> 0x16);
}
