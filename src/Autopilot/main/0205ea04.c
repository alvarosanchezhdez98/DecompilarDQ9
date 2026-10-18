#include <m2c.h>

M2C_UNK func_0205e944(void *, s32);

void func_0205e9f4(void *arg0, s32 arg1) {
    if (arg1 < 1) {
        return;
    }
    if (arg1 > 5) {
        return;
    }
    M2C_FIELD(arg0, s8 *, 0xCC) = (s8) arg1;
    func_0205e944(arg0, M2C_FIELD(arg0, s32 *, 0xC8));
}
