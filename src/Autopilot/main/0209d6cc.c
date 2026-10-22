#include <m2c.h>

s32 func_ov017_021d60f4(s32);
s32 func_0209dccc();
M2C_UNK func_0209f968(s32, s32, s32, s32);

s32 func_0209d6bc(s32 arg0) {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r5;

    temp_r0 = func_0209dccc();
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r5 = func_ov017_021d60f4(arg0);
    temp_r4 = func_ov017_021d60f4(arg0 + 8);
    func_0209f968(temp_r0, temp_r5, temp_r4, func_ov017_021d60f4(arg0 + 0x10));
    return 1;
}
