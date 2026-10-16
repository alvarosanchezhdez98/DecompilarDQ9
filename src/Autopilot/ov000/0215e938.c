#include <m2c.h>


s32 func_ov000_0215e938(void *arg0) {
    u8 temp_r2;

    temp_r2 = M2C_FIELD(arg0, u8 *, 0x8E01);
    if ((u32) temp_r2 >= 0x88U) {
        return 0;
    }
    return (temp_r2 * 0x24) + (s32) (arg0 + 0xEC0);
}
