#include <m2c.h>


s32 func_020a2cc4(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x245) & 2) {
        return 1;
    }
    return 0;
}
