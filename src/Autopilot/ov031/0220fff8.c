#include <m2c.h>

M2C_UNK func_ov031_02211864(M2C_UNK, M2C_UNK);
extern void *data_ov031_0224e580;

s32 func_ov031_0220fff8(void *arg0) {
    s32 temp_r4;

    if ((M2C_FIELD(arg0, s32 *, 8) == 0xD6) && (M2C_FIELD(arg0, s32 *, 0xC) != 0)) {
        temp_r4 = M2C_FIELD(arg0, s32 *, 0x10);
        if (temp_r4 == 0) {
            func_ov031_02211864(6, -0x14);
        }
        M2C_FIELD(data_ov031_0224e580, s32 *, 0x30) = temp_r4;
    }
    return 1;
}
