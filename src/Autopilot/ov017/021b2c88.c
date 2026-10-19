#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020a1e54(M2C_UNK);
M2C_UNK func_020a1f4c(M2C_UNK);
extern M2C_UNK data_02114e20;
extern s32 data_ov017_021d840c;

void func_ov017_021b2c88(s32 arg0) {
    s32 temp_r4;

    if (data_ov017_021d840c != 0) {
        func_020a1f4c(1);
        func_020a1e54(1);
        data_ov017_021d840c = 0;
    }
    temp_r4 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0xC);
    _ZN13SafeAllocator7DestroyEv(arg0 + 0xC);
    func_02012da4(&data_02114e20, temp_r4);
}
