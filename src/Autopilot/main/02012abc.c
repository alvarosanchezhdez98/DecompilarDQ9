#include <m2c.h>


s32 func_02012aac(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x5D) != 0) && (M2C_FIELD(arg0, u8 *, 0x5E) == 0)) {
        return 1;
    }
    return 0;
}
