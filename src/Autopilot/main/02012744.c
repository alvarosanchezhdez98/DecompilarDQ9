#include <m2c.h>


s32 func_02012734(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u16 temp_ip;
    u16 temp_lr;

    temp_lr = M2C_FIELD(arg0, u16 *, 0x20);
    temp_ip = M2C_FIELD(arg0, u16 *, 0x22);
    if ((s32) temp_lr < arg1) {
        return 0;
    }
    if ((s32) temp_lr > (s32) (arg1 + arg3)) {
        return 0;
    }
    if ((s32) temp_ip < arg2) {
        return 0;
    }
    if ((s32) temp_ip <= (s32) (arg2 + arg4)) {
        return 1;
    }
    return 0;
}
