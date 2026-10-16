#include <m2c.h>

M2C_UNK func_ov002_0215a658(void *, s8);
M2C_UNK func_ov002_0215a7b4(void *, s8, s16, s16, s32);

s32 func_ov002_0215753c(void *arg0) {
    s16 temp_r2;
    s32 var_r4;

    var_r4 = -1;
    if (M2C_FIELD(arg0, s16 *, 0x1C12) == 0) {
        if ((s32) M2C_FIELD(arg0, s16 *, 0x1BF0) >= 0) {
            var_r4 = 0x238E;
            func_ov002_0215a658(arg0, M2C_FIELD(arg0, s8 *, 0x1C20));
        }
        temp_r2 = M2C_FIELD(arg0, s16 *, 0x1C22);
        if (((s32) temp_r2 > 0) && (M2C_FIELD(arg0, s16 *, 0x1BEA) == 2)) {
            var_r4 = 0x2366;
            func_ov002_0215a7b4(arg0, M2C_FIELD(arg0, s8 *, 0x1C20), temp_r2, M2C_FIELD(arg0, s16 *, 0x1BE8), 0);
        }
        if (M2C_FIELD(arg0, s32 *, 0x1BBC) == 0x24) {
            var_r4 = 0x125D;
        }
    }
    return var_r4;
}
