#include <m2c.h>


s32 func_ov002_0216364c(void *arg0) {
    if (*M2C_FIELD(arg0, s32 **, 0x130) & 1) {
        return 1;
    }
    return 0;
}
