#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov000_0216fe9c(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 2) = 1;
    M2C_FIELD(arg0, s16 *, 4) = 1;
    M2C_FIELD(arg0, s16 *, 6) = 1;
    memset(arg0 + 8, 0, 8);
    M2C_FIELD(arg0, s8 *, 8) = 0xD;
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    M2C_FIELD(arg0, s8 *, 0x11) = 0;
    M2C_FIELD(arg0, s8 *, 0x13) = 0;
    M2C_FIELD(arg0, s8 *, 0x14) = -1;
    M2C_FIELD(arg0, s8 *, 0x15) = -1;
    M2C_FIELD(arg0, s8 *, 0x18) = -1;
    M2C_FIELD(arg0, s16 *, 0x16) = -1;
    M2C_FIELD(arg0, s8 *, 0x19) = -1;
    M2C_FIELD(arg0, s8 *, 0x1A) = -1;
    M2C_FIELD(arg0, s8 *, 0x1B) = -1;
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s16 *, 0x24) = -1;
    M2C_FIELD(arg0, s8 *, 0x26) = -1;
    M2C_FIELD(arg0, s16 *, 0x1E) = 0;
    M2C_FIELD(arg0, s8 *, 0x27) = 0;
}
