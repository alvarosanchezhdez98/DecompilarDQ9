#include <m2c.h>


u16 func_020bb964(void *arg0, s32 arg1) {
    return (u16) ((u32) (arg1 + 1) % (u32) M2C_FIELD(arg0, u32 *, 4));
}
