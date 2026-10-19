#include <m2c.h>

M2C_UNK _ZN12LightingInfo10InitializeEv(void *);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK _ZN20AtmosphericEffectSet5ResetEv(void *);
M2C_UNK _ZN7Model3D5ClearEv(void *);
s32 _ZN9GameState11GetInstanceEv();
s32 func_0200fb9c(s32);
s32 func_020115a8(s32);
M2C_UNK func_0201e248(void *);
M2C_UNK func_02094d00(void *);
M2C_UNK func_020982b4(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
s32 func_0201201c(s32);
M2C_UNK func_02012fa4(void *);

void func_020134e0(void *arg0) {
    s32 temp_r0;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    M2C_FIELD(arg0, s16 *, 0) = 0;
    M2C_FIELD(arg0, s16 *, 2) = 0;
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x424) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x4C) = 0;
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    M2C_FIELD(arg0, s8 *, 0x476) = 0;
    M2C_FIELD(arg0, s8 *, 0x477) = 0;
    M2C_FIELD(arg0, s32 *, 0x82C) = 0;
    M2C_FIELD(arg0, s8 *, 0x830) = 0;
    M2C_FIELD(arg0, s32 *, 0x428) = 1;
    M2C_FIELD(arg0, s32 *, 0x838) = 0;
    M2C_FIELD(arg0, s32 *, 0x83C) = 0;
    M2C_FIELD(arg0, s8 *, 0x42C) = 0;
    M2C_FIELD(arg0, s32 *, 0x41C) = 0;
    M2C_FIELD(arg0, s32 *, 0x418) = 0;
    M2C_FIELD(arg0, s32 *, 0x478) = 0;
    M2C_FIELD(arg0, s32 *, 0x47C) = 0;
    M2C_FIELD(arg0, s8 *, 0x834) = 0;
    M2C_FIELD(arg0, s8 *, 0x23B8) = 0;
    M2C_FIELD(arg0, s8 *, 0x23B9) = 0;
    M2C_FIELD(arg0, s32 *, 0x420) = 0;
    M2C_FIELD(arg0, s8 *, 0x23BC) = 0;
    M2C_FIELD(arg0, s32 *, 0x276C) = -1;
    M2C_FIELD(arg0, s32 *, 0x2770) = 0;
    M2C_FIELD(arg0, s8 *, 0x831) = 0;
    M2C_FIELD(arg0, s8 *, 0x832) = 0;
    M2C_FIELD(arg0, s8 *, 0x833) = 0;
    M2C_FIELD(arg0, s8 *, 0x281F) = 0;
    M2C_FIELD(arg0, s8 *, 0x2820) = 0;
    M2C_FIELD(arg0, s16 *, 0x27D6) = 0;
    M2C_FIELD(arg0, s8 *, 0x23BB) = -1;
    func_0201e248(arg0 + 0x6C);
    _ZN20AtmosphericEffectSet5ResetEv(arg0 + 0xF4);
    _ZN12LightingInfo10InitializeEv(arg0 + 0x10C);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x54);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x2730);
    _ZN7Model3D5ClearEv(arg0 + 0x498);
    _ZN7Model3D5ClearEv(arg0 + 0x544);
    func_02094d00(arg0 + 0x2724);
    M2C_FIELD(arg0, s32 *, 0x27C4) = 0;
    M2C_FIELD(arg0, s32 *, 0x27B8) = 0;
    M2C_FIELD(arg0, s32 *, 0x27BC) = 0xA000;
    M2C_FIELD(arg0, s32 *, 0x27C0) = 0;
    M2C_FIELD(arg0, s32 *, 0x820) = 0;
    func_02012fa4(arg0 + 0x600);
    memset(arg0 + 0x27DC, 0, 0x40);
    M2C_FIELD(arg0, s8 *, 0x281C) = 0;
    M2C_FIELD(arg0, s8 *, 0x2744) = 0;
    M2C_FIELD(arg0, s8 *, 0x2745) = 1;
    M2C_FIELD(arg0, s8 *, 0x2746) = 0;
    M2C_FIELD(arg0, s16 *, 0x2748) = 0;
    M2C_FIELD(arg0, s32 *, 0x274C) = 1;
    M2C_FIELD(arg0, s32 *, 0x2750) = 1;
    if (func_0200fb9c(temp_r0) != 5) {
        M2C_FIELD(arg0, s16 *, 0x27D8) = 0;
        M2C_FIELD(arg0, s16 *, 0x27DA) = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x281D) = 0;
    M2C_FIELD(arg0, s8 *, 0x281E) = 0;
    if (func_020115a8(temp_r0) != 0) {
        return;
    }
    if ((func_0201201c(temp_r0) != 5) && (func_0200fb9c(temp_r0) != 4) && (func_0200fb9c(temp_r0) != 2)) {
        return;
    }
    func_020982b4(arg0 + 0x840);
    M2C_FIELD(arg0, s16 *, 0x27B4) = 2;
    M2C_FIELD(arg0, s16 *, 0x27B6) = 0;
    M2C_FIELD(arg0, s16 *, 0x2784) = 0;
    M2C_FIELD(arg0, s16 *, 0x2786) = 0x76C;
    M2C_FIELD(arg0, s8 *, 0x2788) = 0;
    M2C_FIELD(arg0, s32 *, 0x2780) = 0;
    M2C_FIELD(arg0, s32 *, 0x2794) = 0x50;
    M2C_FIELD(arg0, s8 *, 0x27D0) = 0;
    M2C_FIELD(arg0, s32 *, 0x2774) = 0x19000;
    M2C_FIELD(arg0, s32 *, 0x2778) = 0x199;
    M2C_FIELD(arg0, s32 *, 0x277C) = 0x38CCC;
}
