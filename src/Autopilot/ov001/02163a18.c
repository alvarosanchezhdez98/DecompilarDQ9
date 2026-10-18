#include <m2c.h>

M2C_UNK func_0205eb48(M2C_UNK *, s32 *, M2C_UNK);
s32 func_ov017_021d60f4();
extern M2C_UNK data_02108760;
extern s32 data_ov001_02165958[0x14];

s32 func_ov001_02163a18(void) {
    s32 temp_r0;

    temp_r0 = func_ov017_021d60f4();
    if ((temp_r0 < 0) || (temp_r0 >= 0x10)) {
        return 0;
    }
    func_0205eb48(&data_02108760, &data_ov001_02165958[temp_r0], 0);
    return 1;
}
