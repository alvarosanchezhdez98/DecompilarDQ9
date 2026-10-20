#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
s32 func_020100f8();
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_020a27ac();
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0218d5c8();
extern M2C_UNK data_02114e20;

void func_ov017_021bf490(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;

    temp_r5 = func_ov017_0218b5b0();
    if ((M2C_FIELD(arg0, u8 *, 0x48) != 0) && (temp_r5 != 0)) {
        func_ov017_0218d5c8();
        M2C_FIELD(arg0, u8 *, 0x48) = 0U;
    }
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x34);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x34);
        func_02012da4(&data_02114e20, temp_r0);
    }
    temp_r0_2 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x4C);
    if (temp_r0_2 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x4C);
        func_02012da4(&data_02114e20, temp_r0_2);
    }
    _ZN9GameState11GetInstanceEv();
    if (func_020100f8() != 0) {
        func_020a27ac();
    }
    if (temp_r5 == 0) {
        return;
    }
    func_0203b4e8(temp_r5, 0x80);
}
