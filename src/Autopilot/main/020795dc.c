#include <m2c.h>


s32 func_020795cc(void *arg0) {
    u8 temp_r0;

    temp_r0 = M2C_FIELD(arg0, u8 *, 0x17D);
    if (temp_r0 & 8) {
        return (u8) ((s32) temp_r0 >> 4) & 3;
    }
    return -1;
}
