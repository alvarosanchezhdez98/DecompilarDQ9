#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
extern M2C_UNK data_02114e20;

void func_ov017_021a9714(void *arg0) {
    s32 temp_r0;

    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0xC);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0xC);
        func_02012da4(&data_02114e20, temp_r0);
    }
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0xC);
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    func_0203b4e8(func_ov017_0218b5b0(), 0xC0);
}
