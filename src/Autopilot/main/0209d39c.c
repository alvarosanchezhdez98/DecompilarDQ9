#include <m2c.h>

s32 func_ov017_021d60f4(s32);
M2C_UNK func_ov017_021d6134(s32, s32);
s32 func_0209dccc();
s32 func_0209fc84(s32, s32);

s32 func_0209d38c(s32 arg0) {
    s32 temp_r0;

    temp_r0 = func_0209dccc();
    if (temp_r0 == 0) {
        return 0;
    }
    func_ov017_021d6134(arg0 + 8, func_0209fc84(temp_r0, func_ov017_021d60f4(arg0)));
    return 1;
}
