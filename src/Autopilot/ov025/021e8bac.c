#include <m2c.h>


void func_ov025_021e8bac(void *arg0, void *arg1) {
    M2C_FIELD(arg1, u8 *, 1) = (u8) M2C_FIELD(arg0, u8 *, 0x30);
    M2C_FIELD(arg1, void **, 8) = (void *) M2C_FIELD(arg0, void **, 0x1D8);
    M2C_FIELD(arg0, void **, 0x1D8) = arg1;
}
