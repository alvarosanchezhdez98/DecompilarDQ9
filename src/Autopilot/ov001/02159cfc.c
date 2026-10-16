#include <m2c.h>

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK strcpy(void *, M2C_UNK *);
extern M2C_UNK data_ov001_02164d10;

void func_ov001_02159cfc(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    memset(arg0 + 4, 0, 0xC);
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    strcpy(arg0 + 0x1C, &data_ov001_02164d10);
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
}
