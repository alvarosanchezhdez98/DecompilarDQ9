#include <m2c.h>

M2C_UNK func_02093ad8(void *, void *, void *, s8);

void func_02093a98(void *arg0) {
    func_02093ad8(arg0, arg0 + 0x1A0, arg0, M2C_FIELD(arg0, s8 *, 0x3CC));
    M2C_FIELD(arg0, s8 *, 0x3CB) = (s8) M2C_FIELD(arg0, s8 *, 0x3CC);
    M2C_FIELD(arg0, s8 *, 0x3CC) = 0;
    M2C_FIELD(arg0, u8 *, 0x3CD) = (u8) (M2C_FIELD(arg0, u8 *, 0x3CD) & ~4);
}
