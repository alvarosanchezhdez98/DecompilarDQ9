#include <m2c.h>

M2C_UNK func_02048120();

void func_020489bc(void *arg0) {
    func_02048120();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x80);
    M2C_FIELD(arg0, s32 *, 0x13C) = 0;
    M2C_FIELD(arg0, s32 *, 0x138) = 0;
    M2C_FIELD(arg0, s8 *, 0x140) = 0;
}
