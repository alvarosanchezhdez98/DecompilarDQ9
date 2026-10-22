#include <m2c.h>

s32 func_ov017_021d60f4(s32);
s32 func_0209dccc();
M2C_UNK func_0209e6ac(s32, s32, s32);

s32 func_0209cebc(s32 arg0) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r0 = func_0209dccc();
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r4 = func_ov017_021d60f4(arg0);
    func_0209e6ac(temp_r0, temp_r4, func_ov017_021d60f4(arg0 + 8));
    return 1;
}
