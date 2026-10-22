#include <m2c.h>

s32 func_0205ec34();
M2C_UNK func_0206eb64(s32, s32, s32);
s32 func_ov017_021d60f4(s32);

s32 func_0209d48c(s32 arg0) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r0 = func_0205ec34();
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r4 = func_ov017_021d60f4(arg0);
    func_0206eb64(temp_r0, temp_r4, func_ov017_021d60f4(arg0 + 8));
    return 1;
}
