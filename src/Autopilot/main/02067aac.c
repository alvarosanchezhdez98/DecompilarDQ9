#include <m2c.h>

M2C_UNK memcpy(u16 *, M2C_UNK, M2C_UNK);

s32 func_02067a9c(s32 arg0, M2C_UNK arg1) {
    u16 sp0;

    memcpy(&sp0, arg1, 2);
    if (((u32) sp0 >= 0xFF01U) && ((u32) sp0 <= 0xFF0DU)) {
        return 1;
    }
    return 0;
}
