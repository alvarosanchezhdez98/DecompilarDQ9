#include <m2c.h>

M2C_UNK CPSi_md5_calc(void *, M2C_UNK *, s32);
M2C_UNK func_ov031_0220ab94(M2C_UNK *, void *, M2C_UNK);
extern M2C_UNK data_ov031_022497a4;

void CPSi_md5_result(void *arg0, M2C_UNK *arg1) {
    s32 temp_r0;
    s32 var_r2;

    func_ov031_0220ab94(arg1, arg0 + 0x10, 8);
    temp_r0 = ((u32) M2C_FIELD(arg0, u32 *, 0x10) >> 3) & 0x3F;
    if (temp_r0 < 0x38) {
        var_r2 = 0x38 - temp_r0;
    } else {
        var_r2 = 0x78 - temp_r0;
    }
    CPSi_md5_calc(arg0, &data_ov031_022497a4, var_r2);
    CPSi_md5_calc(arg0, arg1, 8);
    func_ov031_0220ab94(arg1, arg0, 0x10);
}
