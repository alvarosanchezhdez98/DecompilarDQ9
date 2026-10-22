#include <m2c.h>

s32 _Z11GetBTRandomv();
s32 _Z13NextRandomMaxP6Randomi(s32, s32);
s32 func_ov017_021d60f4(s32);
M2C_UNK func_ov017_021d6134(s32, s32);

s32 func_0209d3cc(s32 arg0) {
    s32 temp_r4;

    temp_r4 = _Z11GetBTRandomv();
    func_ov017_021d6134(arg0 + 8, _Z13NextRandomMaxP6Randomi(temp_r4, func_ov017_021d60f4(arg0) + 1));
    return 1;
}
