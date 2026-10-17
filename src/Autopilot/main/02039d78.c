#include <m2c.h>


s32 func_02039d68(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1CE) & 4) {
        return 1;
    }
    return 0;
}
