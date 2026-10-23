#include <m2c.h>


s32 func_ov017_02195550(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x431E) != 0) {
        return 1;
    }
    if (*M2C_FIELD(arg0, u8 **, 0x441C) != 0) {
        return 1;
    }
    if (M2C_FIELD(arg0, u8 *, 0x42F0) != 0) {
        return 1;
    }
    return 0;
}
