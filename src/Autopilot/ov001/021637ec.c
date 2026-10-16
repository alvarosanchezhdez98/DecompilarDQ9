#include <m2c.h>

M2C_UNK func_0205eb54();
s32 func_ov017_021d60f4();
extern M2C_UNK data_02108760;

s32 func_ov001_021637ec(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r4;

    if (arg1 == 2) {
        temp_r4 = func_ov017_021d60f4();
        func_0205eb54(&data_02108760, temp_r4, func_ov017_021d60f4(arg0 + 8));
    } else if (arg1 == 1) {
        temp_r0 = func_ov017_021d60f4();
        func_0205eb54(&data_02108760, temp_r0, temp_r0);
    }
    return 1;
}
