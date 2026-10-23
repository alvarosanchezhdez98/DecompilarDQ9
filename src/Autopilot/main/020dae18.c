#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020a0c0c();
M2C_UNK func_020a1e54(M2C_UNK);
M2C_UNK func_ov003_0217db88();
extern M2C_UNK data_02114e20;

void func_020dae08(void *arg0) {
    s32 temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        func_ov003_0217db88();
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
        func_020a1e54(1);
    }
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x14);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x14);
        func_02012da4(&data_02114e20, temp_r0);
    }
    func_020a0c0c();
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
