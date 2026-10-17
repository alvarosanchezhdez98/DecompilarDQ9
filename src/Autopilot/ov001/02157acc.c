#include <m2c.h>


void func_ov001_02157acc(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s32 *, 0xC4) > 0) {
        M2C_FIELD(arg0, s32 *, 0x464) = 1;
    }
}
