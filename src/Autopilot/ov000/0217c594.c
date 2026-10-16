#include <m2c.h>

s32 func_02012444(M2C_UNK *, s32);
s32 func_0205da38(void *, M2C_UNK);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_ov000_02184294;

s32 func_ov000_0217c594(void *arg0, s32 arg1) {
    s32 temp_r4;
    u8 temp_r0;

    temp_r0 = M2C_FIELD(arg0, u8 *, 0x956);
    if ((s32) temp_r0 < arg1) {
        M2C_FIELD(arg0, u8 *, 0x956) = (u8) (temp_r0 + 1);
        return 0;
    }
    M2C_FIELD(&data_ov000_02184294, void **, 8) = arg0;
    temp_r4 = func_02012444(&data_02114e30, 0x601);
    if ((temp_r4 | func_0205da38(arg0 + 0x188, 0x14)) != 0) {
        return 1;
    }
    return 0;
}
