#include <m2c.h>

M2C_UNK func_0201bf98(void *, M2C_UNK, M2C_UNK);

void func_0201bf38(void *arg0, M2C_UNK arg1, s8 arg2, s8 arg3, u16 arg4) {
    func_0201bf98(arg0, 0, arg1);
    M2C_FIELD(arg0, s8 *, 0x2745) = arg2;
    M2C_FIELD(arg0, s8 *, 0x2746) = arg3;
    M2C_FIELD(arg0, u16 *, 0x2748) = arg4;
}
