#include <m2c.h>

M2C_UNK CPSi_sha1_calc(void *, M2C_UNK *, s32);
M2C_UNK char_from_long__sha1(M2C_UNK *, void *, M2C_UNK);
extern M2C_UNK data_ov031_022498e4;

void CPSi_sha1_result(void *arg0, M2C_UNK *arg1) {
    s32 temp_r0;
    s32 var_r2;

    char_from_long__sha1(arg1, arg0 + 0x14, 8);
    temp_r0 = ((u32) M2C_FIELD(arg0, u32 *, 0x18) >> 3) & 0x3F;
    if (temp_r0 < 0x38) {
        var_r2 = 0x38 - temp_r0;
    } else {
        var_r2 = 0x78 - temp_r0;
    }
    CPSi_sha1_calc(arg0, &data_ov031_022498e4, var_r2);
    CPSi_sha1_calc(arg0, arg1, 8);
    char_from_long__sha1(arg1, arg0, 0x14);
}
