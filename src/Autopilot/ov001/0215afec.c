#include <m2c.h>

s32 _Z11GetBTRandomv();
s32 _Z17NextRandomBetweenP6Randomii(s32, s32, s32);
s32 func_ov017_021d60f4(s32);
M2C_UNK func_ov017_021d6134(s32, s32);

s32 func_ov001_0215afec(s32 arg0, s32 arg1) {
    s32 temp_r4;
    s32 temp_r5;

    if (arg1 < 2) {
        return 0;
    }
    temp_r5 = _Z11GetBTRandomv();
    temp_r4 = func_ov017_021d60f4(arg0);
    func_ov017_021d6134(arg0 + 0x10, _Z17NextRandomBetweenP6Randomii(temp_r5, temp_r4, func_ov017_021d60f4(arg0 + 8)));
    return 1;
}
