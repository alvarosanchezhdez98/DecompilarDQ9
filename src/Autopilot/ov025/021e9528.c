#include <m2c.h>

s32 func_ov025_021ed2f4(void *);

s32 func_ov025_021e9528(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        return 0;
    }
    if (func_ov025_021ed2f4(arg0 + 0x5E8) != 0) {
        return 1;
    }
    return 0;
}
