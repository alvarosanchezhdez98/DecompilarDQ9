#include <m2c.h>

M2C_UNK func_020e1e24(s32, void *, void *, s8);

void func_020e2604(void *arg0) {
    func_020e1e24(M2C_FIELD(arg0, s32 *, 0x10), arg0 + 0x18, arg0 + 0x1A, M2C_FIELD(arg0, s8 *, 0x14));
    M2C_FIELD(arg0, s16 *, 0x18) = (s16) (M2C_FIELD(arg0, s16 *, 0x18) - 0x10);
    M2C_FIELD(arg0, s16 *, 0x1A) = (s16) (M2C_FIELD(arg0, s16 *, 0x1A) - 2);
}
