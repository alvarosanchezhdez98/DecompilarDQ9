#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_02059cc8(void *arg0) {
    memset(arg0, 0, 0xD4);
    M2C_FIELD(arg0, s16 *, 0xB2) = -1;
    M2C_FIELD(arg0, s16 *, 0xB4) = -1;
    M2C_FIELD(arg0, u8 *, 0xCC) = (u8) ((M2C_FIELD(arg0, u8 *, 0xCC) | 4) & ~8);
}
