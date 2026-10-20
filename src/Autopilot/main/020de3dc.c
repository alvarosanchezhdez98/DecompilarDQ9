#include <m2c.h>


s32 func_020de3cc(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_ip;

    temp_ip = M2C_FIELD(arg0, s32 *, 0x10);
    if ((arg1 == ((u32) (temp_ip * 0x10) >> 0x18)) && (arg2 == ((u32) (temp_ip << 0x16) >> 0x16)) && (arg3 == ((u32) (temp_ip << 0xC) >> 0x16))) {
        return 1;
    }
    return 0;
}
