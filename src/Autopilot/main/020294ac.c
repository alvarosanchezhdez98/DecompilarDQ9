#include <m2c.h>

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_0202949c(void *arg0) {
    M2C_FIELD(arg0, s8 *, 4) = 0;
    memset(arg0 + 4, 0, 0x30);
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
}
