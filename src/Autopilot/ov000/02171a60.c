#include <m2c.h>


s32 func_ov000_02171a60(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x28) & 1) {
        return 1;
    }
    return 0;
}
