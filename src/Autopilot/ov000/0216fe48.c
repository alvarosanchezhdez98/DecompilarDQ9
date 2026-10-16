#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov000_0216fe48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = -1;
    M2C_FIELD(arg0, s32 *, 0x84) = 0;
    M2C_FIELD(arg0, s8 *, 0xA0) = 0;
    M2C_FIELD(arg0, s8 *, 0xA1) = 0;
    memset(arg0 + 0x88, 0, 0x18);
}
