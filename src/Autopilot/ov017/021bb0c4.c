#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov017_021bb0c4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xFC) = 0;
    M2C_FIELD(arg0, s16 *, 0x11A) = 0;
    memset(arg0 + 0x13C, 0, 0x12);
    memset(arg0 + 0x150, 0, 0xA);
    M2C_FIELD(arg0, s32 *, 0x15C) = 0;
    M2C_FIELD(arg0, s8 *, 0xFE) = 0;
}
