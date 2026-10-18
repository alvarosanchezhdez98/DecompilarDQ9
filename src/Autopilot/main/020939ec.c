#include <m2c.h>

M2C_UNK func_020938f0();

void func_020939dc(void *arg0) {
    func_020938f0();
    M2C_FIELD(arg0, u8 *, 0x3C9) = (u8) ((M2C_FIELD(arg0, u8 *, 0x3C9) & ~1) | 1);
}
