#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020a1e54(M2C_UNK);
extern M2C_UNK data_02114e20;

void func_ov017_021bac8c(void *arg0) {
    s32 temp_r4;

    if (M2C_FIELD(arg0, s32 *, 0x20) != 0) {
        func_020a1e54(1);
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
    }
    temp_r4 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0xC);
    _ZN13SafeAllocator7DestroyEv(arg0 + 0xC);
    func_02012da4(&data_02114e20, temp_r4);
}
