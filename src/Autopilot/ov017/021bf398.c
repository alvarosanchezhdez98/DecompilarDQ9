#include <m2c.h>

M2C_UNK _ZN13SafeAllocator5ResetEv(s32);
M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
s32 func_020100f8();
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020397c0(s32);
M2C_UNK func_020727ec(s32);
M2C_UNK func_020a27ac(s32);
extern M2C_UNK data_02114e20;

void func_ov017_021bf398(void *arg0) {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_020100f8();
    temp_r4_2 = _ZN9GameState20GetUnknownGameObjectEv(temp_r4);
    func_020a27ac(temp_r5);
    func_020397c0(temp_r4_2);
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x14);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator5ResetEv(arg0 + 0x14);
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x14);
        func_020727ec(arg0 + 0xC);
        func_02012da4(&data_02114e20, temp_r0);
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
