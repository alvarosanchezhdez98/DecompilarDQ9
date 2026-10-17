#include <m2c.h>

M2C_UNK _Z16SetSubBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
s32 _Z31IsSubBrightnessTransitionActiveP13GameResources();
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_0200fb8c();
M2C_UNK func_020466f4(s32, M2C_UNK);
M2C_UNK func_02074e54(void *);
s32 func_020d6c00();
M2C_UNK func_020dc2d0(M2C_UNK);

void func_ov003_0215445c(void *arg0) {
    s32 temp_r0;
    u8 temp_r1;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_0200fb8c();
    if (M2C_FIELD(arg0, u8 *, 0x58) == 0) {
        M2C_FIELD(arg0, s8 *, 0x5A) = 3;
        return;
    }
    temp_r1 = M2C_FIELD(arg0, u8 *, 0x5B);
    if (temp_r1 == 0) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r0, -0x10, 1);
        M2C_FIELD(arg0, u8 *, 0x5B) = (u8) (M2C_FIELD(arg0, u8 *, 0x5B) + 1);
        return;
    }
    if (temp_r1 != 1) {
        return;
    }
    if (_Z31IsSubBrightnessTransitionActiveP13GameResources() != 0) {
        return;
    }
    func_02074e54(arg0 + 0x38);
    func_020466f4(func_020d6c00(), 1);
    func_020dc2d0(0);
    M2C_FIELD(arg0, s8 *, 0x5A) = 3;
    M2C_FIELD(arg0, u8 *, 0x5B) = 0U;
}
