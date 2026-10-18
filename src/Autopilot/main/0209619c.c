#include <m2c.h>

s32 *func_02096134();

u8 func_0209618c(void) {
    s32 *temp_r0;

    temp_r0 = func_02096134();
    if (temp_r0 != NULL) {
        return (u8) ((u32) (*temp_r0 << 0x12) >> 0x1D);
    }
    return 0U;
}
