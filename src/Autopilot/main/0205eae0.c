#include <m2c.h>

s32 func_0203aa64(void *);
M2C_UNK func_0203aa80(void *, s32);
M2C_UNK func_0203aa98(void *, M2C_UNK);

void func_0205ead0(void *arg0, M2C_UNK arg1, s16 arg2) {
    func_0203aa80(arg0, M2C_FIELD(arg0, s32 *, 0xB8));
    func_0203aa98(arg0, arg1);
    M2C_FIELD(arg0, s16 *, 0xBC) = arg2;
    M2C_FIELD(arg0, s32 *, 0xC0) = func_0203aa64(arg0);
}
