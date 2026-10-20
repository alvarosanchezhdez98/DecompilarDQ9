#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
void *func_020421a0();
M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_02108760;
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;

s32 func_ov017_021aa080(void) {
    s32 temp_r0;
    s32 var_r4;

    temp_r0 = M2C_FIELD(func_020421a0(), s32 *, 0x9A0);
    var_r4 = 0;
    if ((temp_r0 != 3) && (temp_r0 != 0)) {

    } else {
        if ((func_02012444(&data_02114e30, 1) != 0) || (func_02012444(&data_02114e30, 0x200) != 0) || (func_02012444(&data_02114e30, 0x100) != 0) || (func_02012444(&data_02114e30, 0x40) != 0) || (func_02012444(&data_02114e30, 0x80) != 0) || (func_02012444(&data_02114e30, 0x20) != 0) || (func_02012444(&data_02114e30, 0x10) != 0)) {
            var_r4 = 1;
        }
        if (M2C_FIELD(&data_02114e54, u8 *, 0x54) != 0) {
            var_r4 = 1;
        }
    }
    if (var_r4 == 0) {
        return 0;
    }
    func_0205eaa0(&data_02108760, 1, 0);
    return 1;
}
