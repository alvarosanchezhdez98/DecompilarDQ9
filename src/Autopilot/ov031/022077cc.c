#include <m2c.h>

u32 SOCL_InetAtoH();

s32 SOC_InetAtoN(s32 arg0, s32 *arg1) {
    u32 temp_r0;

    temp_r0 = SOCL_InetAtoH();
    if (temp_r0 == 0) {
        return 0;
    }
    *arg1 = ((temp_r0 << 0x18) & 0xFF000000) | (((temp_r0 << 8) & 0xFF0000) | ((u8) (temp_r0 >> 0x18) | ((temp_r0 >> 8) & 0xFF00)));
    return 1;
}
