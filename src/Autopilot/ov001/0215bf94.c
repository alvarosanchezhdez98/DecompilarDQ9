#include <m2c.h>

s32 func_ov017_021d60f4();
M2C_UNK func_ov001_02159ea8();
s32 func_ov001_0215ab20();

s32 func_ov001_0215bf94(s32 arg0) {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = func_ov017_021d60f4();
    temp_r4 = func_ov017_021d60f4(arg0 + 8);
    temp_r0 = func_ov001_0215ab20(temp_r5);
    if (temp_r0 == 0) {
        return 0;
    }
    func_ov001_02159ea8(temp_r0, temp_r4);
    return 1;
}
