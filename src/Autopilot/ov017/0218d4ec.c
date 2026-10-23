#include <m2c.h>


s32 func_ov017_0218d4ec(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, u8 *, 0x4331) & (1 << arg1);
}
