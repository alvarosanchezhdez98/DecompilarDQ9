#include <m2c.h>


u8 func_02047a3c(void *arg0, s32 arg1) {
    if (((u32) (M2C_FIELD(arg0, u8 *, 0x84) << 0x1F) >> 0x1F) != 0) {
        return M2C_FIELD((M2C_FIELD(arg0, s32 *, 8) + (arg1 * 8)), u8 *, 1);
    }
    return 0U;
}
