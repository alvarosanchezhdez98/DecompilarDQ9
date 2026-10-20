#include <m2c.h>

M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
s32 func_020100f8(s32);
M2C_UNK func_02012da4(M2C_UNK *, s32);
M2C_UNK func_020397c0();
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_020a2794();
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0218d5c8();
extern M2C_UNK data_02114e20;

void func_ov017_021ae760(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;

    temp_r0 = func_ov017_0218b5b0();
    M2C_FIELD(arg0, s8 *, 1) = 1;
    if ((M2C_FIELD(arg0, u8 *, 0xB) != 0) && (temp_r0 != 0)) {
        func_ov017_0218d5c8();
        temp_r0_2 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x2C);
        if (temp_r0_2 != 0) {
            _ZN13SafeAllocator7DestroyEv(arg0 + 0x2C);
            func_02012da4(&data_02114e20, temp_r0_2);
        }
        M2C_FIELD(arg0, u8 *, 0xB) = 0U;
    }
    temp_r4 = _ZN9GameState11GetInstanceEv();
    if (_ZN9GameState20GetUnknownGameObjectEv() != 0) {
        func_020397c0();
    }
    if (func_020100f8(temp_r4) != 0) {
        func_020a2794();
    }
    if (temp_r0 == 0) {
        return;
    }
    func_0203b4e8(temp_r0, 0x80);
}
