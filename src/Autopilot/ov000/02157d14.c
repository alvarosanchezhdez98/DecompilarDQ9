#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov000_02157d14(void *arg0) {
    memset(arg0, 0, 0x30);
    M2C_FIELD(arg0, s16 *, 0x1C) = -1;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
}
