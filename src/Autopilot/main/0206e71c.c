#include <m2c.h>

M2C_UNK memcpy(void *, void *, M2C_UNK);

void func_0206e70c(void *arg0) {
    memcpy(arg0 + 0x334, arg0, 0xCE);
    M2C_FIELD(arg0, s32 *, 0x404) = 0;
    memcpy(arg0 + 0x40C, arg0 + 0x323, 0xF);
}
