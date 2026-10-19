#include <m2c.h>

s32 func_ov031_0220f4bc();
s32 func_ov031_022101e0();
s32 func_ov031_02211410();
M2C_UNK ov00_021EC2EC(s32, s32 *, s32);
extern s32 *data_ov031_0224e590;

s32 func_ov031_0221126c(void) {
    s32 var_r4;

    var_r4 = 1;
    if (data_ov031_0224e590 == NULL) {
        return 1;
    }
    *data_ov031_0224e590 = 3;
    if (func_ov031_0220f4bc() == 0) {
        var_r4 = 0;
    }
    if (func_ov031_022101e0() == 0) {
        var_r4 = 0;
    }
    if (var_r4 != 0) {
        ov00_021EC2EC(0x53574300, data_ov031_0224e590, func_ov031_02211410());
        data_ov031_0224e590 = NULL;
    }
    return var_r4;
}
