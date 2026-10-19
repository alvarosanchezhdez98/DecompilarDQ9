#include <m2c.h>

M2C_UNK func_0205eb24(M2C_UNK *, s32, s32);
s32 func_ov017_021d60f4();
M2C_UNK func_ov017_021d6134(s32, s32);
s32 func_ov001_0215a818(s32 *);
extern M2C_UNK data_02108760;

s32 func_ov001_021639ac(s32 arg0, s32 arg1) {
    s32 sp0;
    s32 temp_r0;
    s32 temp_r4;

    temp_r4 = func_ov017_021d60f4();
    if (arg1 >= 2) {
        temp_r0 = func_ov001_0215a818(&sp0);
        if (temp_r0 != 0) {
            func_0205eb24(&data_02108760, temp_r4, temp_r0);
        }
        func_ov017_021d6134(arg0 + 8, sp0);
    } else {
        func_0205eb24(&data_02108760, temp_r4, 0);
    }
    return 1;
}
