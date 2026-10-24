#include <m2c.h>

M2C_UNK _ZN8Object3D6DetachEv();
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
void *func_ov000_02160094(M2C_UNK, s32);
s32 func_ov000_021820bc(M2C_UNK, M2C_UNK, u8, s32 *);
M2C_UNK func_ov017_021917f0(u16, M2C_UNK);

s32 func_ov025_021e73c8(void *arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3) {
    s32 sp0[12];
    u8 temp_r1;
    void *temp_r0;

    if (func_ov000_021820bc(arg3, arg1, M2C_FIELD(arg0, u8 *, 8), sp0) == 0) {
        return 1;
    }
    if (_ZN9GameState20GetGameObjectByIndexEi(_ZN9GameState11GetInstanceEv(), sp0[0]) == 0) {
        return 1;
    }
    _ZN8Object3D6DetachEv();
    temp_r1 = M2C_FIELD(arg0, u8 *, 8);
    if (((u32) temp_r1 >= 0x22U) && ((u32) temp_r1 <= 0x25U)) {
        temp_r0 = func_ov000_02160094(arg1, temp_r1 - 0x22);
        if (temp_r0 != NULL) {
            func_ov017_021917f0(M2C_FIELD(temp_r0, u16 *, 0x20), 1);
        }
    }
    return 1;
}
