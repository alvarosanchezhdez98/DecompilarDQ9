#include <m2c.h>

u32 _ZN8Object3D17SetInheritedAlphaEi(void *, M2C_UNK);
M2C_UNK _ZN8Object3D24TransitionInheritedAlphaEii(void *, M2C_UNK, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK8Object3D10GetField06Ev(void *);
u32 func_0200ff58(s32, s16);

u32 func_02039df4(void *arg0) {
    s32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;

    temp_r0_3 = (u32) (M2C_FIELD(arg0, u8 *, 0xC2) << 0x1A) >> 0x1F;
    if (temp_r0_3 != 0) {
        return temp_r0_3;
    }
    temp_r0_2 = func_0200ff58(_ZN9GameState11GetInstanceEv(), M2C_FIELD(arg0, s16 *, 4));
    if (temp_r0_2 == 0) {
        return temp_r0_2;
    }
    temp_r0 = _ZNK8Object3D10GetField06Ev(arg0) / 100;
    if ((temp_r0 != 0x2B) && (temp_r0 != 0x2D) && (temp_r0 != 0x40) && (temp_r0 != 0x29)) {
        return (u32) temp_r0;
    }
    M2C_FIELD(arg0, u8 *, 0x1CE) = (u8) (M2C_FIELD(arg0, u8 *, 0x1CE) | 4);
    _ZN8Object3D24TransitionInheritedAlphaEii(arg0, 0, 0);
    return _ZN8Object3D17SetInheritedAlphaEi(arg0, 0);
}
