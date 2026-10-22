#include <m2c.h>


s32 func_02088e04(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r0 & 1) {
        return 0;
    }
    if (temp_r0 & 0x10) {
        return 0;
    }
    if (temp_r0 & 0x80000) {
        return 0;
    }
    if (temp_r0 & 8) {
        return 0;
    }
    if (!(temp_r0 & 0x20)) {
        return 1;
    }
    return 0;
}
