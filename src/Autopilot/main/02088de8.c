#include <m2c.h>

s32 func_02088e04();

s32 func_02088dd8(void *arg0) {
    if (func_02088e04() == 0) {
        return 0;
    }
    if (!(M2C_FIELD(arg0, s32 *, 0x18) & 0x1000)) {
        return 1;
    }
    return 0;
}
