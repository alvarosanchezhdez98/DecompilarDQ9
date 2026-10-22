#include <m2c.h>

M2C_UNK _ZN8Object3D21MaybeSetBCFGAnimationEii(void *, u8, s32);
M2C_UNK _ZN8Object3D24MaybeSetRegularAnimationEPKci(void *, s32, s32);

void func_02041538(void *arg0) {
    s32 temp_r1;
    u8 temp_r1_2;

    if (((u32) (M2C_FIELD(arg0, u8 *, 0xD4) << 0x1F) >> 0x1F) != 0) {
        return;
    }
    M2C_FIELD(arg0, u16 *, 0xAC) = (u16) (M2C_FIELD(arg0, u16 *, 0xAC) & ~1);
    temp_r1 = M2C_FIELD(arg0, s32 *, 0xCC);
    if (temp_r1 != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x14) == temp_r1) {
            return;
        }
        _ZN8Object3D24MaybeSetRegularAnimationEPKci(arg0, temp_r1, M2C_FIELD(arg0, s32 *, 0xD0));
        return;
    }
    temp_r1_2 = M2C_FIELD(arg0, u8 *, 0xC4);
    if (temp_r1_2 == M2C_FIELD(arg0, s8 *, 0x18)) {
        return;
    }
    _ZN8Object3D21MaybeSetBCFGAnimationEii(arg0, temp_r1_2, M2C_FIELD(arg0, s32 *, 0xD0));
}
