#include <m2c.h>

s32 func_ov017_021d4ce4(M2C_UNK *, s32);
M2C_UNK func_ov001_0215a9b4();
extern s32 data_ov001_0216580c[7];
extern M2C_UNK data_ov001_02165828;

s32 func_ov001_02153948(s32 arg0) {
    s32 temp_r0;

    temp_r0 = func_ov017_021d4ce4(&data_ov001_02165828, arg0);
    if (temp_r0 == -1) {
        return 0;
    }
    if (temp_r0 != 0) {
        *data_ov001_0216580c = arg0;
        func_ov001_0215a9b4();
    }
    return temp_r0;
}
