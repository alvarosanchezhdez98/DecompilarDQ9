#include <m2c.h>
#pragma optimization_level 4

u32 SOCL_GetHostID();

s32 SOC_GetHostID(void) {
    u32 temp_r0;

    temp_r0 = SOCL_GetHostID();
    return ((temp_r0 << 0x18) & 0xFF000000) | (((temp_r0 << 8) & 0xFF0000) | ((u8) (temp_r0 >> 0x18) | ((temp_r0 >> 8) & 0xFF00)));
}
