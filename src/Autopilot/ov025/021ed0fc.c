#include <m2c.h>


s32 func_ov025_021ed0fc(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x300) == 0) {
        return 1;
    }
    return 0;
}
