#include <m2c.h>

s32 func_ov017_021d60f4();
M2C_UNK func_ov001_0215a6dc();
s32 func_ov001_0215ab20();

s32 func_ov001_021634a8(s32 arg0) {
    s32 temp_r0;

    func_ov017_021d60f4();
    temp_r0 = func_ov001_0215ab20();
    if (temp_r0 == 0) {
        return 0;
    }
    func_ov001_0215a6dc(temp_r0, func_ov017_021d60f4(arg0 + 8));
    return 1;
}
