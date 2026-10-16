#include <m2c.h>

s32 func_ov017_021d60f4();
M2C_UNK func_ov001_0215a4e8();
s32 func_ov001_0215ab20();

s32 func_ov001_0215c5b4(s32 arg0) {
    s32 temp_r0;
    s32 temp_r4;

    func_ov017_021d60f4();
    temp_r0 = func_ov001_0215ab20();
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r4 = func_ov017_021d60f4(arg0 + 8);
    func_ov001_0215a4e8(temp_r0, temp_r4, func_ov017_021d60f4(arg0 + 0x10));
    return 1;
}
