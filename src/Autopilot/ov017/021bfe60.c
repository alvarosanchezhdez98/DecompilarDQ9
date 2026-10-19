#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv(s32);
u32 _ZNK9GameState21GetEffectiveDeltaTimeEv();
s32 func_020100f8(s32);
M2C_UNK func_020397c0();
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_020a27ac();
s32 func_ov017_0218b5b0();

s32 func_ov017_021bfe60(void *arg0) {
    s32 temp_r4;
    s32 temp_r5;
    u16 temp_r1;
    u32 temp_r0;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZNK9GameState21GetEffectiveDeltaTimeEv();
    temp_r1 = M2C_FIELD(arg0, u16 *, 8);
    if (temp_r0 < (u32) temp_r1) {
        M2C_FIELD(arg0, u16 *, 8) = (u16) (temp_r1 - temp_r0);
        return 5;
    }
    M2C_FIELD(arg0, u16 *, 8) = 0U;
    if (_ZN9GameState20GetUnknownGameObjectEv(temp_r4) != 0) {
        func_020397c0();
    }
    temp_r5 = func_ov017_0218b5b0();
    if (func_020100f8(temp_r4) != 0) {
        func_020a27ac();
    }
    if (temp_r5 != 0) {
        func_0203b4e8(temp_r5, 0x80);
    }
    M2C_FIELD(arg0, u16 *, 8) = 0x12CU;
    return 6;
}
