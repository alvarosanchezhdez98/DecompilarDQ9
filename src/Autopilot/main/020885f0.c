#include <m2c.h>


s32 func_020885e0(void *arg0) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r1 & 1) {
        return 0;
    }
    if (temp_r1 & 0x01000000) {
        return 0;
    }
    if ((temp_r1 & 2) && (((u32) (M2C_FIELD(arg0, u16 *, 0x22) << 0x1E) >> 0x1E) == 2)) {
        return 0;
    }
    return 1;
}
