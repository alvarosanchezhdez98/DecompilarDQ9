#include <m2c.h>

M2C_UNK func_ov000_0215a88c(void *, s32, M2C_UNK);
s32 func_ov000_0215e958(void *);
M2C_UNK func_ov000_0215ffc4(s32, s32, M2C_UNK);

s32 func_ov024_021e8ca0(void *arg0, M2C_UNK arg1) {
    s32 temp_r0;
    void *temp_r1;

    temp_r0 = func_ov000_0215e958(M2C_FIELD(arg0, void **, 0x10));
    if (temp_r0 == 0) {
        return 0;
    }
    func_ov000_0215a88c(M2C_FIELD(arg0, void **, 0x10), temp_r0, arg1);
    func_ov000_0215ffc4(M2C_FIELD(arg0, s32 *, 0xC), temp_r0, 1);
    temp_r1 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(temp_r1, u8 *, 0x8E02) = (u8) (M2C_FIELD(temp_r1, u8 *, 0x8E02) + 1);
    return temp_r0;
}
