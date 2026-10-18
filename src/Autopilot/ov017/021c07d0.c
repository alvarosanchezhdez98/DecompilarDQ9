#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020a1f4c(M2C_UNK);
extern M2C_UNK data_02114e20;

void func_ov017_021c07d0(void *arg0) {
    s32 temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x1C) != 0) {
        func_020a1f4c(1);
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    }
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 8);
    if (temp_r0 == 0) {
        return;
    }
    _ZN13SafeAllocator7DestroyEv(arg0 + 8);
    func_02012da4(&data_02114e20, temp_r0);
}
