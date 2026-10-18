#include <m2c.h>


void func_020863e0(void *arg0) {
    u16 temp_r2;
    u16 temp_r2_2;

    temp_r2 = M2C_FIELD(arg0, u16 *, 0x6C);
    if ((u32) temp_r2 < (u32) M2C_FIELD(arg0, u16 *, 0x1C)) {
        M2C_FIELD(arg0, u16 *, 0x1C) = temp_r2;
    }
    temp_r2_2 = M2C_FIELD(arg0, u16 *, 0x6E);
    if ((u32) temp_r2_2 < (u32) M2C_FIELD(arg0, u16 *, 0x1E)) {
        M2C_FIELD(arg0, u16 *, 0x1E) = temp_r2_2;
    }
}
