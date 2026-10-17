#include <m2c.h>


s32 func_0203f1c8(void *arg0, u32 arg1) {
    if ((u32) M2C_FIELD(arg0, u32 *, 0x18) <= arg1) {
        return 0;
    }
    return (arg1 * 0x14) + M2C_FIELD(arg0, s32 *, 0x1C);
}
