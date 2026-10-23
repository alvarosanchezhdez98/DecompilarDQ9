#include <m2c.h>

void *func_020421a0();

s32 func_ov001_0215e588(void) {
    void *temp_r0;

    temp_r0 = func_020421a0();
    if (temp_r0 == NULL) {
        return 0;
    }
    M2C_FIELD(temp_r0, u8 *, 0x195B) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x195B) | 0x80);
    return 1;
}
