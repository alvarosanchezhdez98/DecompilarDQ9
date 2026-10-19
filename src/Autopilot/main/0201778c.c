#include <m2c.h>


s32 func_0201777c(void *arg0, s32 arg1) {
    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, u8 *, 0x476) <= arg1)) {
        return 0;
    }
    return (arg1 * 0x368) + M2C_FIELD(arg0, s32 *, 0x478);
}
