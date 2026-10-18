#include <m2c.h>


s32 func_0204c7e0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xD4) == 0) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x9C) != 0) {
        return 1;
    }
    return 0;
}
