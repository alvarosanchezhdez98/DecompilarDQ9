#include <m2c.h>

M2C_UNK VectorizedMemset(s32, M2C_UNK, M2C_UNK);
M2C_UNK _ZN13SafeAllocator11CreateTypeAEPvj(void *, s32, M2C_UNK);
M2C_UNK _ZN13SafeAllocator5ResetEv(void *);
void *_ZN13SafeAllocator8AllocateEj(void *, s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv(s32);
s32 func_020100f8(s32);
s32 func_02012d88(M2C_UNK *, M2C_UNK);
M2C_UNK func_020397c0();
M2C_UNK func_020397cc(s32, M2C_UNK);
M2C_UNK func_0203b4d8(s32, M2C_UNK);
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_02074af4(void *);
M2C_UNK func_020a0c0c();
M2C_UNK func_020a0cc4(M2C_UNK);
M2C_UNK func_020a1df8(M2C_UNK);
M2C_UNK func_020a27ac();
M2C_UNK func_020a27b8();
M2C_UNK func_020a28b0(s32, M2C_UNK);
M2C_UNK func_ov003_0216ae0c(void *, void *);
s32 func_ov003_0216af14(void *);
M2C_UNK func_ov003_0216d63c(void *);
M2C_UNK func_ov003_0217f118(void *);
M2C_UNK func_ov003_0217f194(void *);
M2C_UNK func_ov003_0217f1b8(void *);
s32 func_ov017_0218b5b0();
s32 func_ov017_021959b4();
extern M2C_UNK data_02114e20;

void func_ov003_0217ef58(void *arg0) {
    s32 temp_r6 = _ZN9GameState11GetInstanceEv();
    s32 temp_r0;
    void *temp_r0_2;
    s32 temp_r5;

    s32 temp_r1 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_r1 == 0) {
        func_02074af4(arg0 + 0x2A);
        func_0203b4d8(func_ov017_0218b5b0(), 0xC0);
        func_020a0cc4(0x1E800);
        temp_r0 = func_02012d88(&data_02114e20, 0xB000);
        if (temp_r0 == 0) {
            func_020a0c0c();
            M2C_FIELD(arg0, s8 *, 1) = 1;
            return;
        }
        VectorizedMemset(temp_r0, 0, 0xB000);
        _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0x14, temp_r0, 0xB000);
        _ZN13SafeAllocator5ResetEv(arg0 + 0x14);
        temp_r0_2 = _ZN13SafeAllocator8AllocateEj(arg0 + 0x14, 0x1414);
        M2C_FIELD(arg0, void **, 0xC) = temp_r0_2;
        if (temp_r0_2 == NULL) {
            func_020a0c0c();
            M2C_FIELD(arg0, s8 *, 1) = 1;
            return;
        }
        func_020a1df8(3);
        func_ov003_0216d63c(M2C_FIELD(arg0, void **, 0xC));
        func_ov003_0216ae0c(M2C_FIELD(arg0, void **, 0xC), arg0 + 0x14);
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s16 *, 0xA) = (s16) M2C_FIELD(arg0, s32 *, 8);
        func_020397cc(_ZN9GameState20GetUnknownGameObjectEv(temp_r6), 1);
        func_020100f8(temp_r6);
        func_020a27b8();
        M2C_FIELD(arg0, s32 *, 0x10) = 1;
        return;
    }
    if (temp_r1 == 1) {
        if (func_ov003_0216af14(M2C_FIELD(arg0, void **, 0xC)) == 0) {
            M2C_FIELD(arg0, s32 *, 0x10) = 2;
        }
        func_ov017_021959b4();
        if ((func_ov017_021959b4() != 0) && (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s16 *, 4) != 5)) {
            func_ov003_0217f194(arg0);
            M2C_FIELD(arg0, s32 *, 0x10) = 3;
            return;
        }
        return;
    }
    if (temp_r1 == 2) {
        func_ov003_0217f118(arg0);
        _ZN9GameState20GetUnknownGameObjectEv(temp_r6);
        func_020397c0();
        temp_r5 = func_020100f8(temp_r6);
        func_020a27ac();
        func_020a28b0(temp_r5, 2);
        func_0203b4e8(func_ov017_0218b5b0(), 0xC0);
        M2C_FIELD(arg0, s32 *, 0x10) = -1;
        return;
    }
    if (temp_r1 != 3) {
        return;
    }
    if (func_ov003_0216af14(M2C_FIELD(arg0, void **, 0xC)) != 0) {
        return;
    }
    func_ov003_0217f1b8(arg0);
}
