#include <m2c.h>

s32 func_020bc0a4(s16);

s32 func_0209c6bc(void *arg0) {
    if (func_020bc0a4(M2C_FIELD(arg0, s16 *, 0xB8)) != 0) {
        return 1;
    }
    return 0;
}
