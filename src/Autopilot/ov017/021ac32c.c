#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState20GetUnknownGameObjectEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);
s32 func_020100f8(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020397c0();
s32 func_020421a0();
M2C_UNK func_02043124(s32);
M2C_UNK func_02043204();
M2C_UNK func_02094a00();
M2C_UNK func_02094ab0();
M2C_UNK func_020a0c0c();
M2C_UNK func_020a28b0(s32, M2C_UNK);
extern M2C_UNK data_02114e20;

void func_ov017_021ac32c(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;
    s32 temp_r5;

    temp_r4 = func_020421a0();
    func_02043204();
    func_02043124(temp_r4);
    func_02094a00();
    func_02094ab0();
    temp_r5 = _ZN9GameState11GetInstanceEv();
    _ZN9GameState20GetUnknownGameObjectEv();
    func_020397c0();
    temp_r0 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x10);
    if (temp_r0 != 0) {
        _ZN13SafeAllocator7DestroyEv(arg0 + 0x10);
        func_02012da4(&data_02114e20, temp_r0);
        func_020a0c0c();
    }
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    temp_r0_2 = func_020100f8(temp_r5);
    if (temp_r0_2 == 0) {
        return;
    }
    func_020a28b0(temp_r0_2, 3);
}
