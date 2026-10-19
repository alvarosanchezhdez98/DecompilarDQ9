#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
s32 func_02094a00();
M2C_UNK func_02094ab0(s32);
M2C_UNK func_02094b38(s32, s32);
s32 func_ov017_0218b5b0();
extern M2C_UNK data_02114e20;

void func_ov017_021a92a0(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = func_02094a00();
    func_02094b38(temp_r0, 0x205);
    func_02094ab0(temp_r0);
    temp_r0_2 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x264);
    if (temp_r0_2 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x264);
        func_02012da4(&data_02114e20, temp_r0_2);
    }
    func_0203b4e8(func_ov017_0218b5b0(), 0x40);
    *(s32 *)0x04000000 = (*(s32 *)0x04000000 & ~0x1F00) | (M2C_FIELD(arg0, s32 *, 0x24) << 8);
}
