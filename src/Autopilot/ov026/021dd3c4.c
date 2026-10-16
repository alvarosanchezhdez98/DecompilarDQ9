#include <m2c.h>


s32 func_ov026_021dd3c4(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x138), s32 *, 0x18) & 0x2000) {
        return 1;
    }
    return 0;
}
