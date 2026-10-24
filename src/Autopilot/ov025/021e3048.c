#include <m2c.h>

M2C_UNK func_ov025_021e2f54(s32, s32, M2C_UNK);
M2C_UNK func_ov025_021e3084(s32);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e3048(s32 arg0, s32 arg1, s32 arg2, M2C_UNK arg3) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(&data_ov025_021ef988, void **, 0xC);
    func_ov025_021e3084(temp_r4 + 0x540);
    M2C_FIELD(temp_r4, s32 *, 0x540) = arg1;
    func_ov025_021e2f54(temp_r4 + 0x540, arg1, arg3);
    return 1;
}
