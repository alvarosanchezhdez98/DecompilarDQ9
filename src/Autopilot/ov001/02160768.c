#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
M2C_UNK _ZN8Object3D10EnableFlagEi(s32, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
s32 func_020100bc(s32);
M2C_UNK func_020100c4(s32, s32);
void *func_02010768();
M2C_UNK func_0204a120(s32);
M2C_UNK func_0204a3f0(s32, s32);
M2C_UNK func_0204a440(s32, s32);
M2C_UNK func_0204a464(s32, s32);
M2C_UNK func_0204a488(s32, s32);
M2C_UNK func_0204a5dc(s32, s32);
s32 func_ov017_021d60f4(s32);
s32 func_ov017_021d612c(s32);
s32 func_ov001_0215ad2c(s32);
extern s32 data_ov001_021658b8[8];

s32 func_ov001_02160768(s32 arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r11;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 temp_r9;
    void *temp_r8;

    temp_r9 = _ZN9GameState11GetInstanceEv();
    temp_r10 = *data_ov001_021658b8;
    temp_r8 = func_02010768();
    temp_r4 = func_ov017_021d60f4(arg0);
    temp_r7 = func_ov017_021d612c(arg0 + 8);
    temp_r6 = func_ov017_021d612c(arg0 + 0x10);
    temp_r11 = func_ov017_021d612c(arg0 + 0x18);
    temp_r5 = func_ov017_021d60f4(arg0 + 0x20);
    temp_r4_2 = func_ov001_0215ad2c(temp_r4);
    temp_r4_3 = func_ov001_0215ad2c(temp_r5);
    temp_r0 = _ZN9GameState20GetGameObjectByIndexEi(temp_r9, temp_r4_2);
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r0_2 = _ZN9GameState20GetGameObjectByIndexEi(temp_r9, temp_r4_3);
    if (temp_r0_2 == 0) {
        return 0;
    }
    temp_r10_2 = _ZN13SafeAllocator8AllocateEj(temp_r10, 0x268);
    M2C_FIELD(temp_r8, s32 *, 4) = func_020100bc(temp_r9);
    func_0204a120(temp_r10_2);
    func_0204a3f0(temp_r10_2, temp_r0);
    func_0204a440(temp_r10_2, temp_r7);
    func_0204a464(temp_r10_2, temp_r6);
    func_0204a488(temp_r10_2, temp_r11);
    func_0204a5dc(temp_r10_2, temp_r0_2);
    _ZN8Object3D10EnableFlagEi(temp_r0, 1);
    _ZN8Object3D10EnableFlagEi(temp_r0, 0x20);
    func_020100c4(temp_r9, temp_r10_2);
    return 1;
}
