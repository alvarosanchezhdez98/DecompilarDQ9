#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
extern M2C_UNK data_02114e20;

void func_ov017_021aeea8(s32 arg0) {
    s32 temp_r0;

    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x2C);
    if (temp_r0 == 0) {
        return;
    }
    _ZN13SafeAllocator7DestroyEv(arg0 + 0x2C);
    func_02012da4(&data_02114e20, temp_r0);
}
