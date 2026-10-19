#include <m2c.h>

M2C_UNK func_0209953c(M2C_UNK);

void func_02028c64(void *arg0, s32 arg1) {
    if (arg1 < 0x10) {
        M2C_FIELD(arg0, u16 *, 4) = (u16) (M2C_FIELD(arg0, u16 *, 4) | (1 << arg1));
        return;
    }
    func_0209953c(5);
}
