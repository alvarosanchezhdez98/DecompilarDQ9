#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _Z22UnlockAndSetBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZN9StaffRoll6UpdateEi(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
s32 func_ov001_02153994();
s32 func_ov001_02156858(void *);

u16 func_ov001_02155d54(void *arg0) {
    s32 temp_r0;
    s32 temp_r4;
    s8 var_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r4 = func_ov017_0218b5b0();
    temp_r0 = M2C_FIELD(arg0, s32 *, 0x160);
    if (temp_r0 != 0) {
        if (_ZN9StaffRoll6UpdateEi(temp_r0, 2) != 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        M2C_FIELD(arg0, s8 *, 0x164) = var_r0;
    }
    if (func_ov001_02156858(arg0) != 0) {
        _Z22UnlockAndSetBrightnessP13GameResourcesii(temp_r4, -0x10, 0x1E);
        M2C_FIELD(arg0, s32 *, 0x15C) = 1;
        return 0xEU;
    }
    if (func_ov001_02153994() != 1) {
        return M2C_FIELD(arg0, u16 *, 0xA);
    }
    return 0xFU;
}
