#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov000_02160030(void *arg0) {
    memset(arg0, 0, 0x28);
    M2C_FIELD(arg0, s16 *, 6) = -1;
    memset(arg0 + 0x18, 0, 0xE);
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
}
