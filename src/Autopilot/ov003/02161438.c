#include <m2c.h>

s8 *func_ov003_02160bd0(void *, s32);
M2C_UNK func_ov003_02167a5c(s32, M2C_UNK, s32);

void func_ov003_02161438(void *arg0) {
    s32 var_r5;
    s8 *temp_r0;

    var_r5 = -1;
    temp_r0 = func_ov003_02160bd0(arg0, (M2C_FIELD(arg0, s16 *, 0x48C) - 0x15) + (M2C_FIELD(arg0, s8 *, 0x49F) * 4));
    if (temp_r0 != NULL) {
        var_r5 = (s32) (*temp_r0 << 0x1A) >> 0x1A;
    }
    func_ov003_02167a5c(M2C_FIELD(arg0, s32 *, 0x318), 6, var_r5);
}
