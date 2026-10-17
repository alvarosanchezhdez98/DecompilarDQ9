#include <m2c.h>

M2C_UNK _Z16SetSubBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
s32 _Z31IsSubBrightnessTransitionActiveP13GameResources();
M2C_UNK func_020466f4(s32, M2C_UNK);
s32 func_020d6c00();
M2C_UNK func_020dc2d0(M2C_UNK);
M2C_UNK func_ov003_02167370(s32);
s32 func_ov017_0218b5b0();

s32 func_ov003_02160e34(void *arg0) {
    s32 temp_r0;
    s32 temp_r6;
    s32 var_r4;
    u8 temp_r1;

    var_r4 = 0;
    temp_r6 = func_020d6c00();
    temp_r0 = func_ov017_0218b5b0();
    temp_r1 = M2C_FIELD(arg0, u8 *, 0x4A8);
    if (temp_r1 == 0) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r0, -0x10, 8);
        M2C_FIELD(arg0, u8 *, 0x4A8) = (u8) (M2C_FIELD(arg0, u8 *, 0x4A8) + 1);
    } else if ((temp_r1 == 1) && (_Z31IsSubBrightnessTransitionActiveP13GameResources() == 0)) {
        func_ov003_02167370(M2C_FIELD(arg0, s32 *, 0x318));
        M2C_FIELD(arg0, u8 *, 0x4A8) = 0U;
        var_r4 = 1;
        func_020466f4(temp_r6, 0x41);
        func_020dc2d0(0);
        M2C_FIELD(arg0, s32 *, 0x464) = (s32) (M2C_FIELD(arg0, s32 *, 0x464) & ~0x800);
    }
    return var_r4;
}
