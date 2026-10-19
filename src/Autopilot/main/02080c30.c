#include <m2c.h>

void *func_02081da8();

void func_02080c20(void) {
    void *temp_r0;

    temp_r0 = func_02081da8();
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, u8 *, 0xC5) = (u8) (M2C_FIELD(temp_r0, u8 *, 0xC5) & ~0x20);
    }
}
