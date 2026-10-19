#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_020de868(void *arg0) {
    memset(arg0, 0, 0x14);
    M2C_FIELD(arg0, s8 *, 0x14) = 0;
}
