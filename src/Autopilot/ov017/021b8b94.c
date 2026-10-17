#include <m2c.h>

s32 func_ov000_0216265c();

s32 func_ov017_021b8b94(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x6AC) == 0) {
        return 0;
    }
    return func_ov000_0216265c();
}
