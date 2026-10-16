#include <m2c.h>


s32 func_ov000_0215516c(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x138), s32 *, 0x14) & 0x08000000) {
        return 1;
    }
    return 0;
}
