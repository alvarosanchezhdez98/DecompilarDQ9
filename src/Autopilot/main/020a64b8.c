#include <m2c.h>


s32 func_020a64a8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xA) != 0) {
        return 1;
    }
    return 0;
}
