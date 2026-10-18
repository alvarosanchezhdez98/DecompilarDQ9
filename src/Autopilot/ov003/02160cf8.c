#include <m2c.h>

M2C_UNK _Z16SetSubBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
s32 _Z31IsSubBrightnessTransitionActiveP13GameResources(s32);
M2C_UNK _ZN13SafeAllocator5ResetEv(void *);
M2C_UNK func_020466e4(s32, M2C_UNK);
s32 func_020d6c00();
M2C_UNK func_ov003_02161438(void *);
M2C_UNK func_ov003_0216724c(s32 *, void *);
M2C_UNK func_ov003_021672e4(s32 *, M2C_UNK, M2C_UNK);
s32 func_ov003_0216759c(s32 *);
s32 func_ov017_0218b5b0();

s32 func_ov003_02160cf8(void *arg0) {
    s32 temp_r6;
    s32 temp_r7;
    s32 var_r4;
    u8 temp_r1;

    temp_r7 = func_ov017_0218b5b0();
    temp_r6 = func_020d6c00();
    temp_r1 = M2C_FIELD(arg0, u8 *, 0x4A8);
    var_r4 = 0;
    if (temp_r1 == 0) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r7, -0x10, 8);
        M2C_FIELD(arg0, u8 *, 0x4A8) = (u8) (M2C_FIELD(arg0, u8 *, 0x4A8) + 1);
    } else if (temp_r1 == 1) {
        if (_Z31IsSubBrightnessTransitionActiveP13GameResources(temp_r7) == 0) {
            func_020466e4(temp_r6, 1);
            _ZN13SafeAllocator5ResetEv(arg0 + 0x23C);
            func_ov003_021672e4(M2C_FIELD(arg0, s32 **, 0x318), 0, -1);
            *M2C_FIELD(arg0, s32 **, 0x318) = M2C_FIELD(arg0, s32 *, 0x398);
            func_ov003_0216724c(M2C_FIELD(arg0, s32 **, 0x318), arg0 + 0x23C);
            M2C_FIELD(arg0, u8 *, 0x4A8) = (u8) (M2C_FIELD(arg0, u8 *, 0x4A8) + 1);
        }
    } else if (temp_r1 == 2) {
        if (func_ov003_0216759c(M2C_FIELD(arg0, s32 **, 0x318)) != 0) {
            func_ov003_02161438(arg0);
            M2C_FIELD(arg0, u8 *, 0x4A8) = (u8) (M2C_FIELD(arg0, u8 *, 0x4A8) + 1);
        }
    } else if (temp_r1 == 3) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r7, 0, 8);
        M2C_FIELD(arg0, u8 *, 0x4A8) = (u8) (M2C_FIELD(arg0, u8 *, 0x4A8) + 1);
    } else if ((temp_r1 == 4) && (_Z31IsSubBrightnessTransitionActiveP13GameResources(temp_r7) == 0)) {
        M2C_FIELD(arg0, u8 *, 0x4A8) = 0U;
        var_r4 = 1;
        M2C_FIELD(arg0, s32 *, 0x464) = (s32) (M2C_FIELD(arg0, s32 *, 0x464) & ~0x400);
    }
    return var_r4;
}
