#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_0209c20c(M2C_UNK *);
M2C_UNK func_0209c6d8(M2C_UNK *, s32);
s32 func_ov017_021d60f4();
extern M2C_UNK data_02109bf4;

s32 func_ov001_021637a8(void) {
    s32 temp_r4;

    temp_r4 = func_ov017_021d60f4();
    func_0209c20c(&data_02109bf4);
    func_0209c6d8(&data_02109bf4, temp_r4);
    return 1;
}
