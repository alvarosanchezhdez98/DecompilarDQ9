#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK strcpy(void *, M2C_UNK *);
extern M2C_UNK data_ov001_02164d10;

void func_ov001_02158828(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    memset(arg0 + 4, 0, 0xC);
    memset(arg0 + 0x10, 0, 0xC);
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    strcpy(arg0 + 0x28, &data_ov001_02164d10);
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
}
