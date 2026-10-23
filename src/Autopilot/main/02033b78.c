#include <m2c.h>

M2C_UNK func_02033ce8();

void func_02033b68(void *arg0, u8 arg1) {
    u8 temp_r2;

    temp_r2 = M2C_FIELD(arg0, u8 *, 0xBE);
    if (temp_r2 == arg1) {
        return;
    }
    M2C_FIELD(arg0, u8 *, 0xBF) = temp_r2;
    M2C_FIELD(arg0, u8 *, 0xBE) = arg1;
    func_02033ce8();
}
