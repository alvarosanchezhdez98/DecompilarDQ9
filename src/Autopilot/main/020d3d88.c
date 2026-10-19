#include <m2c.h>


s32 func_020d3d78(void *arg0, s32 arg1) {
    if (arg1 < (s32) M2C_FIELD(arg0, s32 *, 0xB4)) {
        return (arg1 * 0x24) + (s32) arg0;
    }
    return 0;
}
