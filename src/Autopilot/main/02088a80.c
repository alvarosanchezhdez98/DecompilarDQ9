#include <m2c.h>


s32 func_02088a70(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x14) & 1) {
        return 0;
    }
    if (!(M2C_FIELD(arg0, s32 *, 0x18) & 0x40)) {
        return 1;
    }
    return 0;
}
