#include <m2c.h>

s32 func_020de194(s32);

u32 func_ov003_02175898(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        return 0U;
    }
    return (u32) (M2C_FIELD(arg0, u16 *, 0x86C) * func_020de194(arg1)) / 100U;
}
