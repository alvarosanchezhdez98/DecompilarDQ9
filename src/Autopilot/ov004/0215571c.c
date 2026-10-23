#include <m2c.h>

M2C_UNK _Z18RefreshMenuObject6P10MenuScriptt(M2C_UNK, M2C_UNK);
M2C_UNK _Z19SetMenuObjectFValueP10MenuScripttih(M2C_UNK, M2C_UNK, s16, M2C_UNK);
extern void *data_ov004_021707c4;

s32 func_ov004_0215571c(M2C_UNK arg0) {
    s16 temp_r4;
    s16 var_r2;

    temp_r4 = M2C_FIELD(data_ov004_021707c4, s16 *, 0xE);
    var_r2 = (s16) ((s32) (temp_r4 * 0x64) / (s16) M2C_FIELD(data_ov004_021707c4, s16 *, 0xC));
    if ((var_r2 == 0) && (temp_r4 == 0)) {
        var_r2 = 0;
    }
    if ((var_r2 == 0) && (temp_r4 != 0)) {
        var_r2 = 1;
    }
    if ((s32) var_r2 > 0x64) {
        var_r2 = 0x64;
    }
    if ((s32) var_r2 < 0) {
        var_r2 = 0;
    }
    _Z19SetMenuObjectFValueP10MenuScripttih(arg0, 0x13, var_r2, 0xF);
    _Z19SetMenuObjectFValueP10MenuScripttih(arg0, 0x14, temp_r4, 0xF);
    _Z18RefreshMenuObject6P10MenuScriptt(arg0, 0x10);
    return 0;
}
