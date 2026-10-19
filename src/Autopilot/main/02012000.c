#include <m2c.h>

void *func_020108f0();

u32 func_02011ff0(void) {
    void *temp_r0;

    temp_r0 = func_020108f0();
    if (temp_r0 != NULL) {
        return (u32) (M2C_FIELD(temp_r0, u8 *, 0x56B) << 0x1C) >> 0x1C;
    }
    return 0U;
}
