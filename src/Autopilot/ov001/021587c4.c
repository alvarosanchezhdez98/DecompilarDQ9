#include <m2c.h>

M2C_UNK memcpy(void *, s32, M2C_UNK);

s32 func_ov001_021587c4(void *arg0, void *arg1) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg1, s32 *, 0xA20);
    if (temp_r1 == 0) {
        return 0;
    }
    memcpy(arg1 + 0x58, temp_r1 + 0x74, 0xC);
    M2C_FIELD(arg1, s32 *, 0x58) = (s32) (M2C_FIELD(arg1, s32 *, 0x58) + M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(arg1, s32 *, 0x5C) = (s32) (M2C_FIELD(arg1, s32 *, 0x5C) + M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(arg1, s32 *, 0x60) = (s32) (M2C_FIELD(arg1, s32 *, 0x60) + M2C_FIELD(arg0, s32 *, 0xC));
    return 1;
}
