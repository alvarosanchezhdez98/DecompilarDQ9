#include <m2c.h>


s32 func_ov031_022115a4(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x28) != 0x41435753) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x2C) == 0x10000) {
        return 1;
    }
    return 0;
}
