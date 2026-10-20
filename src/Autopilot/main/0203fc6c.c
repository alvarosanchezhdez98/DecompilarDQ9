#include <m2c.h>


s32 func_0203fc5c(void *arg0, f32 arg1) {
    if (arg1 <= 0.0f) {
        return 0;
    }
    M2C_FIELD(arg0, f32 *, 0x40) = arg1;
    return 1;
}
