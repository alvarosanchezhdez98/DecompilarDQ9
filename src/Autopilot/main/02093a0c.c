#include <m2c.h>

M2C_UNK func_020939ac();

void func_020939fc(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x3C9) = (u8) (M2C_FIELD(arg0, u8 *, 0x3C9) & ~1);
    func_020939ac();
}
