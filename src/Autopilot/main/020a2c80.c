#include <m2c.h>


s32 func_020a2c70(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2C5) != 0) {
        M2C_FIELD(arg0, s8 *, 0x2C4) = 1;
        return 1;
    }
    return 0;
}
