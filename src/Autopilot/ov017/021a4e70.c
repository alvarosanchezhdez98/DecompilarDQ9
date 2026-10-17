#include <m2c.h>


s32 func_ov017_021a4e70(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s8 *, 0x4354) <= 0) {
        return 1;
    }
    return 0;
}
