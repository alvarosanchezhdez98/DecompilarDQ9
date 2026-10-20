#include <m2c.h>

M2C_UNK func_020a0db8(s32, s32, M2C_UNK, M2C_UNK);

void func_0202ee58(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_020a0db8(arg0 + 0x194, arg0 + 0x10, arg1, arg2);
    M2C_FIELD(arg0, s32 *, 0x168) = (s32) (M2C_FIELD(arg0, s32 *, 0x168) & ~2);
}
