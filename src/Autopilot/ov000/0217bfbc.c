#include <m2c.h>

s32 func_02012444(M2C_UNK *, s32);
s32 func_0205d97c(s32);
M2C_UNK func_ov000_0217629c(void *);
M2C_UNK func_ov000_02176e3c(s32, void *, s8, s32, s32, s32);
M2C_UNK func_ov000_0217ab8c(void *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_ov000_02184294;

s32 func_ov000_0217bfbc(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_r7;
    s32 temp_r7_2;
    s32 var_r0;

    temp_r7 = func_02012444(&data_02114e30, 0x601);
    temp_r7_2 = temp_r7 | func_02012444(&data_02114e30, 0x802);
    if (func_0205d97c(M2C_FIELD(arg0, s32 *, 0x38)) == 2) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if ((temp_r7_2 | var_r0) != 0) {
        M2C_FIELD(arg0, s8 *, 0x444) = 0;
        func_ov000_0217629c(arg0);
        M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x18)), s8 *, 0x10) = 0;
        M2C_FIELD(arg0, s8 *, 0x18) = (s8) (M2C_FIELD(arg0, s8 *, 0x18) - 1);
        func_ov000_0217ab8c(arg0, arg1, arg2);
        func_ov000_02176e3c(M2C_FIELD(&data_ov000_02184294, s32 *, 8), arg0, M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x18)), s8 *, 0x10), M2C_FIELD(&data_ov000_02184294, s32 *, 4), M2C_FIELD(&data_ov000_02184294, s32 *, 0), 0);
    }
    return -1;
}
