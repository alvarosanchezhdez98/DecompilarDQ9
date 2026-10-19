#include <m2c.h>

M2C_UNK func_0203aa80(void *, s32);

void func_0205eb08(void *arg0) {
    func_0203aa80(arg0, M2C_FIELD(arg0, s32 *, 0xB8));
    M2C_FIELD(arg0, s32 *, 0xC0) = (s32) M2C_FIELD(arg0, s32 *, 0xB8);
}
