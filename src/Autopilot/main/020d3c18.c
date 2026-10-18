#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_020d3c08(void *arg0) {
    memset(arg0, 0, 0xB4);
    M2C_FIELD(arg0, s32 *, 0xB4) = 0;
}
