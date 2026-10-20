#include <m2c.h>


s32 func_020885b4(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x14) & 2) && (((u32) (M2C_FIELD(arg0, u16 *, 0x22) << 0x1E) >> 0x1E) == 1)) {
        return 1;
    }
    return 0;
}
