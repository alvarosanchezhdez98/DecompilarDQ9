#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
s32 func_02057924();
M2C_UNK func_02057f00(s32, M2C_UNK);
M2C_UNK func_020a0c0c();
M2C_UNK func_020bb740(s32);
M2C_UNK func_020bb92c(s32);
extern M2C_UNK data_02114e20;

void func_ov017_021a6b30(s32 arg0) {
    s32 temp_r0;

    func_02057f00(func_02057924(), 0xC);
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x10);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x10);
        func_02012da4(&data_02114e20, temp_r0);
    }
    func_020bb740(arg0 + 0x24);
    func_020bb92c(arg0 + 0x4C);
    func_020a0c0c();
}
