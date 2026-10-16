#include <m2c.h>


s32 func_ov000_02156af0(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x138), s32 *, 0x18) & 0x800) {
        return 1;
    }
    return 0;
}
