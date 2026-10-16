#include <m2c.h>


s32 func_ov025_021ed2f4(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x150) == 0) && (M2C_FIELD(arg0, u16 *, 0x15E) == 0)) {
        return 1;
    }
    return 0;
}
