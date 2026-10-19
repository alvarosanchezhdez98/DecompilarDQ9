#include <m2c.h>


s32 func_0204be78(void *arg0) {
    if (((s32) (M2C_FIELD(arg0, u16 *, 2) & 0x3E0) >> 5) != 0) {
        return 1;
    }
    return 0;
}
