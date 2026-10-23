#include <m2c.h>


s32 func_ov001_02158ab8(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 8) == 0) && (M2C_FIELD(arg0, s32 *, 0x10) == 0) && (M2C_FIELD(arg0, s32 *, 0x18) == 0) && (M2C_FIELD(arg0, s32 *, 0x20) == 0)) {
        return 1;
    }
    return 0;
}
