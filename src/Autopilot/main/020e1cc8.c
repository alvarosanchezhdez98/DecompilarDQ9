#include <m2c.h>


void func_020e1cb8(void *arg0) {
    void *temp_r1;
    void *temp_r2;

    temp_r2 = M2C_FIELD(arg0, void **, 4);
    M2C_FIELD(temp_r2, u8 *, 0x3F) = (u8) (M2C_FIELD(temp_r2, u8 *, 0x3F) & ~1);
    temp_r1 = M2C_FIELD(arg0, void **, 4);
    M2C_FIELD(temp_r1, u8 *, 0x3F) = (u8) (M2C_FIELD(temp_r1, u8 *, 0x3F) | 2);
}
