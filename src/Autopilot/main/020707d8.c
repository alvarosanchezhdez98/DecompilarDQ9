#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState21GetEffectiveDeltaTimeEv();
M2C_UNK func_0207051c(void *, u16, s32);

void func_020707c8(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r8;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZNK9GameState21GetEffectiveDeltaTimeEv();
    temp_r8 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_r8 > 0) {
        M2C_FIELD(arg0, f32 *, 0xC) = (f32) (M2C_FIELD(arg0, f32 *, 0xC) + ((f32) temp_r0 * (((f32) M2C_FIELD(arg0, u8 *, 4) - M2C_FIELD(arg0, f32 *, 0xC)) / (f32) temp_r8)));
    }
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 8) - temp_r0;
    M2C_FIELD(arg0, s32 *, 8) = temp_r0_2;
    if (temp_r0_2 <= 0) {
        M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(arg0, u8 *, 4);
        M2C_FIELD(arg0, s32 *, 8) = 0;
        if (M2C_FIELD(arg0, u8 *, 4) == 1) {
            M2C_FIELD(arg0, s8 *, 0) = 0;
        }
    }
    func_0207051c(arg0, M2C_FIELD(arg0, u16 *, 2), (s32) M2C_FIELD(arg0, f32 *, 0xC));
    if ((s32) M2C_FIELD(arg0, s32 *, 8) > 0) {
        return;
    }
    temp_r0_3 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_r0_3 <= 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 8) = (s32) (16.667f * (f32) temp_r0_3);
    M2C_FIELD(arg0, u8 *, 4) = 1U;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
}
