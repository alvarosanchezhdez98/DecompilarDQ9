#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0206f510(void *arg0) {
    memset(arg0, 0, 4);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    memset(arg0 + 8, -1, 8);
    memset(arg0 + 0x10, 0, 0x20);
}
