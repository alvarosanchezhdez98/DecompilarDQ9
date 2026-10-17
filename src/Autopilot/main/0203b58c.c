#include <m2c.h>


s32 func_0203b57c(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        return (s32) M2C_FIELD(arg0, f32 *, 0xC);
    }
    return (s32) M2C_FIELD(arg0, f32 *, 0x18);
}
