#include <m2c.h>

M2C_UNK _Z16SetSubBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
s32 _Z31IsSubBrightnessTransitionActiveP13GameResources();
s32 func_ov017_0218b5b0();

void func_ov003_02173af4(void *arg0) {
    s32 temp_r0;
    u8 temp_r1;

    temp_r0 = func_ov017_0218b5b0();
    temp_r1 = M2C_FIELD(arg0, u8 *, 0xEF);
    if (temp_r1 == 0) {
        _Z16SetSubBrightnessP13GameResourcesii(temp_r0, -0x10, 0x18);
        M2C_FIELD(arg0, u8 *, 0xEF) = 1U;
        return;
    }
    if (temp_r1 != 1) {
        return;
    }
    if (_Z31IsSubBrightnessTransitionActiveP13GameResources() == 0) {
        M2C_FIELD(arg0, s8 *, 0xED) = 6;
        M2C_FIELD(arg0, u8 *, 0xEF) = 0U;
    }
}
