#include <m2c.h>

M2C_UNK func_ov031_0223fa0c();
M2C_UNK func_ov031_0223fa20();
M2C_UNK ov38_02220B60(s32 *, M2C_UNK);
s32 ov38_02222C10(M2C_UNK);
extern s32 data_ov031_02290dbc;
extern s32 data_ov031_02290dc4;

s32 ov38_02220EB8(s32 *arg0, M2C_UNK arg1) {
    s32 temp_r0;

    func_ov031_0223fa0c();
    temp_r0 = ov38_02222C10(arg1);
    *arg0 = temp_r0;
    data_ov031_02290dc4 = temp_r0;
    func_ov031_0223fa20();
    if ((s32) *arg0 >= 0) {
        return 1;
    }
    ov38_02220B60(arg0, arg1);
    data_ov031_02290dbc = 3;
    return 0;
}
