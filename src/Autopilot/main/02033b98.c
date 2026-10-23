#include <m2c.h>

M2C_UNK func_02033ce8();

void func_02033b88(void *arg0, u8 arg1) {
    M2C_FIELD(arg0, u8 *, 0xBF) = (u8) M2C_FIELD(arg0, u8 *, 0xBE);
    M2C_FIELD(arg0, u8 *, 0xBE) = arg1;
    func_02033ce8();
}
