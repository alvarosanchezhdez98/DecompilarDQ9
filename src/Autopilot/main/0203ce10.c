#include <m2c.h>


s32 func_0203ce00(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x5C) & 2) {
        return M2C_FIELD(arg0, s32 *, 0x64);
    }
    return M2C_FIELD(arg0, s32 *, 0x60);
}
