#include <m2c.h>

M2C_UNK _ZN13SafeAllocator5ResetEv(s32);
M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
M2C_UNK func_020100f8();
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020727ec(s32);
M2C_UNK func_020a27ac();
extern M2C_UNK data_02114e20;

void func_020d8484(void *arg0) {
    s32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    func_020100f8();
    func_020a27ac();
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x14);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator5ResetEv(arg0 + 0x14);
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x14);
        func_020727ec(arg0 + 0xC);
        func_02012da4(&data_02114e20, temp_r0);
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
