#include <m2c.h>


s32 func_ov017_0219a370(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s32 *, 0x4078) >= 4) {
        return 1;
    }
    return 0;
}
