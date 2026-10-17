#include <m2c.h>


s32 func_ov017_021b8b54(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0x6B4) == 0) {
        return 1;
    }
    return 0;
}
