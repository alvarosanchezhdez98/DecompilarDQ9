#include <m2c.h>


s32 func_020882f8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x14) & 0x10) {
        return 1;
    }
    return 0;
}
