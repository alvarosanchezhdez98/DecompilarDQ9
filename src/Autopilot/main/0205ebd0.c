#include <m2c.h>

M2C_UNK func_0203aa80(void *, s32);
M2C_UNK func_0203aa98(void *, M2C_UNK);

void func_0205ebc0(void *arg0, M2C_UNK arg1, s16 arg2) {
    func_0203aa80(arg0, M2C_FIELD(arg0, s32 *, 0xC0));
    func_0203aa98(arg0, arg1);
    M2C_FIELD(arg0, s16 *, 0xC4) = arg2;
}
