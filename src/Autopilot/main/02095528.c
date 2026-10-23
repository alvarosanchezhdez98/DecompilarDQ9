#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_02095518(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    M2C_FIELD(arg0, s32 *, 0x4C4) = -1;
    memset(arg0, 0, 0xA0);
    memset(arg0 + 0xAC, 0xFF, 0xCC);
    memset(arg0 + 0x178, 0, 0x330);
    memset(arg0 + 0x4A8, 0, 0x1A);
}
