#include <m2c.h>


s32 func_02088418(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_ip;

    temp_ip = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_ip & 1) {
        return 0;
    }
    if ((temp_ip & 0x01000000) && (arg2 != 0x1FC) && (arg2 != 0x20F)) {
        return 0;
    }
    if (temp_ip & 8) {
        return 0;
    }
    if ((temp_ip & 0x80000) && (arg1 == ((u32) (M2C_FIELD(arg0, u16 *, 0x22) << 0x1A) >> 0x1C))) {
        return 0;
    }
    return 1;
}
