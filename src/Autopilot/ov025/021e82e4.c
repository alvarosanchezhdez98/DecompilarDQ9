#include <m2c.h>

s32 func_ov000_02160130();
M2C_UNK func_ov000_021636ac();
M2C_UNK func_ov000_02163710(s32, M2C_UNK);

s32 func_ov025_021e82e4(void *arg0) {
    s32 temp_r0;

    temp_r0 = func_ov000_02160130();
    if (M2C_FIELD(arg0, u8 *, 8) != 0) {
        func_ov000_02163710(temp_r0, 1);
    } else {
        func_ov000_021636ac();
    }
    return 1;
}
