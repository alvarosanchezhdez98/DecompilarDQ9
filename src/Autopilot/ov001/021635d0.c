#include <m2c.h>

M2C_UNK func_0205eabc();
M2C_UNK func_020bc078();
u32 func_ov017_021d60f4();
extern M2C_UNK data_02108760;
extern s32 data_ov001_02165958[0x14];

s32 func_ov001_021635d0(s32 arg0, s32 arg1) {
    s32 *temp_r4;
    u32 temp_r0;
    u32 var_r2;

    temp_r0 = func_ov017_021d60f4();
    if (temp_r0 >= 0x10U) {
        return 0;
    }
    temp_r4 = &data_ov001_02165958[temp_r0];
    if (data_ov001_02165958[temp_r0] == 0) {
        return 0;
    }
    var_r2 = 0;
    if (arg1 >= 2) {
        var_r2 = func_ov017_021d60f4(arg0 + 8);
    }
    func_0205eabc(&data_02108760, temp_r4, var_r2);
    func_020bc078(temp_r4);
    return 1;
}
