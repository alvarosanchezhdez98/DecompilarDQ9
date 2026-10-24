#include <m2c.h>

s32 func_02057924();
void *func_02058658(s32, void *);
s32 func_ov000_021820bc(s32, s32, u8, s32 *);
void **func_ov025_021e8cf0(s32, u8);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e5014(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp0[8];
    s32 var_r5;
    s32 var_r6;
    void **temp_r0;
    void *var_r4;
    void *var_r7;

    var_r7 = arg0;
    var_r6 = arg1;
    var_r5 = arg3;
    temp_r0 = func_ov025_021e8cf0(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC), M2C_FIELD(var_r7, u8 *, 9));
    if (temp_r0 == NULL) {
        return 1;
    }
    var_r4 = *temp_r0;
    var_r4 = func_02058658(func_02057924(), var_r4);
    if (var_r4 == NULL) {
        return 1;
    }
    if (func_ov000_021820bc(var_r5, var_r6, M2C_FIELD(var_r7, u8 *, 8), sp0) != 1) {
        M2C_FIELD(var_r4, s16 *, 0xB2) = -1;
        return 1;
    }
    M2C_FIELD(var_r4, s16 *, 0xB2) = (s16) sp0[0];
    return 1;
}
