#include <m2c.h>


s32 func_02088660(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x18) & 0x80) {
        return 1;
    }
    return 0;
}
