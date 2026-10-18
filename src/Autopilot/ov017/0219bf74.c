#include <m2c.h>

M2C_UNK _ZN13SafeAllocator5ResetEv(s32);
s32 func_02012fe4();
M2C_UNK func_02013750(s32, M2C_UNK);
M2C_UNK func_0203b4a0(s32, M2C_UNK);
M2C_UNK func_0203b4d8(s32, M2C_UNK);
s32 func_ov017_0218b5b0();

s32 func_ov017_0219bf74(void) {
    s32 temp_r4;

    temp_r4 = func_ov017_0218b5b0();
    func_02013750(func_02012fe4(), 1);
    _ZN13SafeAllocator5ResetEv(temp_r4 + 0x38);
    func_0203b4d8(temp_r4, 2);
    func_0203b4a0(temp_r4, 4);
    return temp_r4 + 0x38;
}
