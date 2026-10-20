#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0203be8c(void *arg0) {
    memset(arg0, 0, 0x20);
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x21) = 0;
    M2C_FIELD(arg0, s16 *, 0x22) = -1;
    M2C_FIELD(arg0, s8 *, 0x24) = 0;
}
