#include <m2c.h>


s32 func_ov016_0218ef2c(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x20) == 0) {
        return 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x28) != 0) {
        return 0x80;
    }
    return 0x100;
}
