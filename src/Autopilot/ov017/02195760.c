#include <m2c.h>


s32 func_ov017_02195760(void *arg0) {
    if (*M2C_FIELD(arg0, u8 **, 0x441C) == 0) {
        return 1;
    }
    return 0;
}
