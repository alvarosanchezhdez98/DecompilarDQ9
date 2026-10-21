#include <m2c.h>

s32 func_020deb08();

s32 func_020deb24(void *arg0, s32 arg1) {
    s32 temp_r0;

    temp_r0 = func_020deb08();
    if ((arg1 < 0) || (arg1 >= temp_r0)) {
        return 0;
    }
    return M2C_FIELD(arg0, s32 *, 0xC) + (arg1 << 5);
}
