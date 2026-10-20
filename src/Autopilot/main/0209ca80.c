#include <m2c.h>

M2C_UNK func_0209c2e0(void *, u8, M2C_UNK);

void func_0209ca70(void *arg0, s32 arg1) {
    if (arg1 < 1) {
        return;
    }
    if (arg1 > 5) {
        return;
    }
    M2C_FIELD(arg0, s8 *, 0xCC) = (s8) arg1;
    func_0209c2e0(arg0, M2C_FIELD(arg0, u8 *, 0xCD), 0);
}
