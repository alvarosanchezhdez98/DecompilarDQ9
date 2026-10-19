#include <m2c.h>


s32 func_0204bdf0(void *arg0) {
    if ((M2C_FIELD(arg0, u16 *, 2) & 0x1F) == 3) {
        return 1;
    }
    return 0;
}
