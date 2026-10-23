#include <m2c.h>

M2C_UNK _Z20ClearMenuObjectFlagsP10MenuScriptth(M2C_UNK, s32, M2C_UNK);
s32 func_ov004_02156e2c(M2C_UNK, M2C_UNK);

s32 func_ov004_0215b710(M2C_UNK arg0) {
    s32 temp_r0;

    temp_r0 = func_ov004_02156e2c(arg0, 0x65);
    if (temp_r0 >= 0) {
        _Z20ClearMenuObjectFlagsP10MenuScriptth(arg0, temp_r0 + 0x38C, 8);
    }
    return 0;
}
