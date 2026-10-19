#include <m2c.h>


s32 func_020999d8(void *arg0, u32 arg1) {
    if ((u32) M2C_FIELD(arg0, u32 *, 4) <= arg1) {
        return 0;
    }
    return M2C_FIELD(arg0, s32 *, 0) + (arg1 * 0x10);
}
