#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov000_0215fef0(void *arg0) {
    memset(arg0, 0, 0x20);
    memset(arg0 + 0xE, -1, 6);
    M2C_FIELD(arg0, s16 *, 0xC) = -1;
}
