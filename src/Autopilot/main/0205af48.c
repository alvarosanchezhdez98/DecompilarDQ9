#include <m2c.h>

s32 func_0205b008(M2C_UNK, void *, M2C_UNK, M2C_UNK, s32, s32);

void func_0205af38(M2C_UNK arg0, void *arg1, s8 arg2, s8 arg3) {
    if ((arg1 != NULL) && (func_0205b008(arg0, arg1, 0, 0x300, 8, arg2 | (u16) (arg3 * 2)) == 0)) {
        M2C_FIELD(arg1, s8 *, 0x23) = arg2;
        M2C_FIELD(arg1, s8 *, 0x24) = arg3;
    }
}
