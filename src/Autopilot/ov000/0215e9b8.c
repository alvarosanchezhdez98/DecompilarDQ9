#include <m2c.h>


void *func_ov000_0215e9b8(void *arg0) {
    u8 temp_r1;

    temp_r1 = M2C_FIELD(arg0, u8 *, 0x8E03);
    if ((u32) temp_r1 >= 0xFCU) {
        return NULL;
    }
    return arg0 + 0x5480 + (temp_r1 * 8);
}
