#include <m2c.h>


s8 func_02011518(void *arg0, u32 arg1) {
    if (arg1 < (u32) M2C_FIELD(arg0, u8 *, 0x5721)) {
        return M2C_FIELD((arg0 + arg1), s8 *, 0x571D);
    }
    return -1;
}
