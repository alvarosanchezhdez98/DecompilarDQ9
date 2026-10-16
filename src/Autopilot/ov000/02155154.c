#include <m2c.h>


s32 func_ov000_02155154(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x138), s32 *, 0x18) & 0x1000) {
        return 1;
    }
    return 0;
}
