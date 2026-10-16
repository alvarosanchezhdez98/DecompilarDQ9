#include <m2c.h>

void *func_ov000_02161318();

void func_ov000_021754e0(void) {
    void *temp_r0;

    temp_r0 = func_ov000_02161318();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, u8 *, 0x43C) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x43C) | 2);
    }
}
