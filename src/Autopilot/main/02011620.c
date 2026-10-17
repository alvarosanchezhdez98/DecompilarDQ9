#include <m2c.h>


s32 func_02011610(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0x63DA) != 0) {
        return 1;
    }
    return 0;
}
