#include <m2c.h>

s32 func_0202e09c();

s32 func_020100cc(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x3B0) != 0) && (func_0202e09c() & 2)) {
        return M2C_FIELD(arg0, s32 *, 0x3B0);
    }
    return 0;
}
