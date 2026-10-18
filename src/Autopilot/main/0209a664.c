#include <m2c.h>


s32 func_0209a654(void *arg0, u32 arg1) {
    if ((u32) M2C_FIELD(arg0, u32 *, 4) <= arg1) {
        return 0;
    }
    return (arg1 * 0xC) + M2C_FIELD(arg0, s32 *, 0);
}
