#include <m2c.h>


s32 func_ov000_0217542c(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x118) == 2) {
        return 1;
    }
    return 0;
}
