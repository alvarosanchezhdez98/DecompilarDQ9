#include <m2c.h>


u8 func_0207c694(s32 arg0, u32 arg1) {
    if (arg1 > 7U) {
        return 0xFFU;
    }
    return M2C_FIELD((arg0 + arg1), u8 *, 0xC28);
}
