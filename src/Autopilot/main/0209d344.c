#include <m2c.h>

s32 func_ov017_021d60f4(s32);
M2C_UNK func_ov017_021d6134(s32, u16);
s32 func_02094d6c();
s32 func_02096134(s32, s32);

s32 func_0209d334(s32 arg0) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = func_02094d6c();
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r0_2 = func_02096134(temp_r0, func_ov017_021d60f4(arg0));
    if (temp_r0_2 == 0) {
        return 0;
    }
    func_ov017_021d6134(arg0 + 0x10, M2C_FIELD((temp_r0_2 + (func_ov017_021d60f4(arg0 + 8) * 2)), u16 *, 0xA));
    return 1;
}
