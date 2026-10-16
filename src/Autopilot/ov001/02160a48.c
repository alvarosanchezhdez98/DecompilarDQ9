#include <m2c.h>

s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0219b578();
s32 func_ov017_021d60f4();

s32 func_ov001_02160a48(s32 arg0) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = func_ov017_021d60f4();
    temp_r4 = func_ov017_021d60f4(arg0 + 8);
    func_ov017_0219b578(func_ov017_0218b5b0(), temp_r5, temp_r4);
    return 1;
}
