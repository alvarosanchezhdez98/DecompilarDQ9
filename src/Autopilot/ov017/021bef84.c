#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
extern M2C_UNK data_02114e20;

void func_ov017_021bef84(s32 arg0) {
    s32 temp_r0;
    s32 temp_r5;

    temp_r5 = func_ov017_0218b5b0();
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x44);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x44);
        func_02012da4(&data_02114e20, temp_r0);
    }
    func_0203b4e8(temp_r5, 0xC0);
}
