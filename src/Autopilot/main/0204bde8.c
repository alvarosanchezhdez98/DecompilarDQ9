#include <m2c.h>


s32 func_0204bdd8(void *arg0) {
    if ((M2C_FIELD(arg0, u16 *, 2) & 0x1F) == 2) {
        return 1;
    }
    return 0;
}
