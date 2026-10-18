#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
u32 _ZNK9GameState21GetEffectiveDeltaTimeEv(s32);
s32 func_0202ae18();
s32 func_0202ae24();
M2C_UNK func_0202b0f4(s32);
M2C_UNK func_0202c21c(s32, u8);
s32 func_0202c508(s32);
s32 func_0202c578(s32, u8);
s32 func_0205e488(s32);
s32 func_020936f8();
M2C_UNK func_02094030(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_ov003_02171e1c(void *, void *);
M2C_UNK func_ov017_021d1810(M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov003_02171764(void *arg0) {
    s32 temp_r7;
    s32 temp_r4;
    s32 temp_r5;
    u32 temp_r0;

    temp_r7 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_0202ae18();
    temp_r5 = func_0202ae24();
    if (func_0202c578(temp_r4, M2C_FIELD(arg0, u8 *, 0x199)) != 0) {
        if (func_0202c508(temp_r4) != 0) {
            func_ov017_021d1810(4, -1, 0);
            func_02094030(func_020936f8(), 4, -1, 0);
        }
        func_0202c21c(temp_r4, M2C_FIELD(arg0, u8 *, 0x199));
    }
    temp_r0 = _ZNK9GameState21GetEffectiveDeltaTimeEv(temp_r7);
    M2C_FIELD(arg0, u32 *, 0x72C) = temp_r0;
    if (temp_r0 > 0xBB8U) {
        func_0202b0f4(temp_r4);
        M2C_FIELD(arg0, s8 *, 0) = 4;
        return;
    }
    if ((M2C_FIELD(arg0, s32 *, 0x720) != 0) && (M2C_FIELD(arg0, s32 *, 0x71C) != 0)) {
        func_ov003_02171e1c(arg0, arg0 + 0x2AE);
        func_0202b0f4(temp_r4);
        M2C_FIELD(arg0, s8 *, 0) = 4;
    }
    if (func_0205e488(temp_r5) != 0) {
        M2C_FIELD(arg0, s32 *, 0x720) = 1;
    }
}
