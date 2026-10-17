#include <m2c.h>


s32 func_0201bfc0(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, u8 *, 0x2744) & (1 << arg1);
}
