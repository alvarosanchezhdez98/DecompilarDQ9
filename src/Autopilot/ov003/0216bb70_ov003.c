#include <m2c.h>
#pragma optimization_level 4

M2C_UNK VectorizedMemset(s32, M2C_UNK, M2C_UNK);
M2C_UNK _ZN13SafeAllocator11CreateTypeAEPvj(void *, s32, M2C_UNK);
M2C_UNK _ZN13SafeAllocator5ResetEv(void *);
M2C_UNK _ZN13SafeAllocator7DestroyEv(void *);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(void *);
s32 _ZNK9GameState12GetTickCountEv(s32);
s32 func_02012d88(M2C_UNK *, M2C_UNK);
M2C_UNK func_02012da4(M2C_UNK *, s32);
void *func_020421a0();
M2C_UNK func_ov003_0215c568(void *, void *);
M2C_UNK func_ov003_0215c650(void *);
M2C_UNK func_ov003_0215c800(void *);
s32 func_ov003_0215c924(void *, s32);
M2C_UNK func_ov003_0216d8d4(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK data_02114e20;

void func_ov003_0216bb70(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;
    u8 temp_r6;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    if (M2C_FIELD(arg0, s16 *, 6) == 0) {
        memset(M2C_FIELD(func_020421a0(), s32 *, 0x5C), 0, 0x960);
        temp_r0 = func_02012d88(&data_02114e20, 0x10000);
        VectorizedMemset(temp_r0, 0, 0x10000);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x12D4, temp_r0, 0x10000);
        _ZN13SafeAllocator5ResetEv(arg0 + 0x12D4);
        func_ov003_0215c650(arg0 + 0x14);
        func_ov003_0215c568(arg0 + 0x14, arg0 + 0x12D4);
        M2C_FIELD(arg0, s8 *, 0x404) = 1;
        M2C_FIELD(arg0, s16 *, 6) = 1;
    }
    if ((M2C_FIELD(arg0, s16 *, 6) == 1) && (func_ov003_0215c924(arg0 + 0x14, _ZNK9GameState12GetTickCountEv(temp_r4)) != 0)) {
        M2C_FIELD(arg0, s16 *, 6) = 2;
    }
    if (M2C_FIELD(arg0, s16 *, 6) == 2) {
        temp_r6 = M2C_FIELD(arg0, u8 *, 0x405);
        func_ov003_0215c800(arg0 + 0x14);
        temp_r0_2 = _ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0x12D4);
        if (temp_r0_2 != 0) {
            _ZN13SafeAllocator7DestroyEv(arg0 + 0x12D4);
            func_02012da4(&data_02114e20, temp_r0_2);
        }
        if (temp_r6 == 0) {
            M2C_FIELD(arg0, s16 *, 4) = 7;
            M2C_FIELD(arg0, s16 *, 6) = 0;
            return;
        }
        *(s32 *)0x04000000 = (*(s32 *)0x04000000 & ~0x1F00) | 0x1700;
        M2C_FIELD(arg0, s16 *, 0xA) = 3;
        M2C_FIELD(func_020421a0(), s32 *, 0x998) = 1;
        func_ov003_0216d8d4(arg0, 0x29, -1, -1, -1);
        M2C_FIELD(arg0, s16 *, 4) = 1;
        M2C_FIELD(arg0, s16 *, 6) = 0;
        M2C_FIELD(arg0, s16 *, 8) = 0;
        M2C_FIELD(arg0, u8 *, 0x13EC) = (u8) (M2C_FIELD(arg0, u8 *, 0x13EC) | 1);
    }
}
