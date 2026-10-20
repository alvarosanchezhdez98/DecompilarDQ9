#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_020dfe88(void *);

void func_020dfc40(void *arg0) {
    memset(arg0, 0, 0xC);
    M2C_FIELD(arg0, s16 *, 0xC) = -1;
    M2C_FIELD(arg0, s32 *, 0x10) = -1;
    func_020dfe88(arg0);
}
