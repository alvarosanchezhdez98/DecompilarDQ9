#include <m2c.h>


s32 func_02088bf0(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r0 & 1) {
        return 0;
    }
    if (!(temp_r0 & 0x20000)) {
        return 1;
    }
    return 0;
}
