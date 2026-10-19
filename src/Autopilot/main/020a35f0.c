#include <m2c.h>


s32 func_020a35e0(void *arg0, u32 arg1) {
    if (arg1 >= 4U) {
        return 0;
    }
    return M2C_FIELD(arg0, u8 *, 0x34) & (1 << arg1);
}
