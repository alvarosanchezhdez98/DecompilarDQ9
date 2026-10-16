#include <m2c.h>


s32 func_ov024_021fe698(void *arg0, s32 arg1) {
    if (M2C_FIELD((arg0 + arg1), u8 *, 0x10) == 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 0x38) = arg1;
    return 1;
}
