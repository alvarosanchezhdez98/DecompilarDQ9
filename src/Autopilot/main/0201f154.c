#include <m2c.h>


s32 func_0201f144(void *arg0, s32 arg1) {
    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, s32 *, 8) <= arg1)) {
        return 0;
    }
    return (arg1 * 0xC) + M2C_FIELD(arg0, s32 *, 0);
}
