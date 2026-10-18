#include <m2c.h>

M2C_UNK _Z24fix32SignedAngleDistanceii(s32, s16);
s32 _Z8fix32absi();
s32 _ZN8Object3D24MaybeSetRegularAnimationEPKci(void *, M2C_UNK *, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
s32 func_02032424(s32, void *);
M2C_UNK func_02033834(void *, s32);
extern M2C_UNK data_020efa3c;

void func_02033920(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (arg1 == M2C_FIELD(arg0, s16 *, 4)) {
        return;
    }
    temp_r0_2 = _ZN9GameState20GetGameObjectByIndexEi(temp_r0, arg1);
    if (temp_r0_2 == 0) {
        return;
    }
    func_02033834(arg0, func_02032424(temp_r0_2 + 0x44, arg0 + 0x44));
    if (arg2 == 0) {
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0xBE) != 0) {
        return;
    }
    _Z24fix32SignedAngleDistanceii(M2C_FIELD(arg0, s32 *, 0x54), M2C_FIELD(arg0, s16 *, 0xAE));
    if (_Z8fix32absi() <= 0x1000) {
        return;
    }
    if ((s32) M2C_FIELD(arg0, s16 *, 0xB0) > 0x10C) {
        return;
    }
    if (_ZN8Object3D24MaybeSetRegularAnimationEPKci(arg0, &data_020efa3c, 0x11) != 0) {
        M2C_FIELD(arg0, u16 *, 0xC4) = (u16) (M2C_FIELD(arg0, u16 *, 0xC4) | 0x8000);
    }
}
