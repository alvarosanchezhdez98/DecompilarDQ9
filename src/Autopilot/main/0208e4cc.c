#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0208e4bc(void *arg0) {
    memset(arg0, 0, 4);
    memset(arg0 + 0x10, 0, 0x20);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}
