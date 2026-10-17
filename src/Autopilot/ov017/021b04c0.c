#include <m2c.h>


u8 func_ov017_021b04c0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x28) != 0) {
        M2C_FIELD(arg0, s8 *, 0x21) = 0;
        M2C_FIELD(arg0, s8 *, 0x22) = 0;
        return 7U;
    }
    return M2C_FIELD(arg0, u8 *, 0xA);
}
