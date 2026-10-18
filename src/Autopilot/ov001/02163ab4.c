#include <m2c.h>

s32 func_ov017_021d60f4();
extern M2C_UNK data_02109bf4;

s32 func_ov001_02163ab4(void) {
    s32 var_r0;

    if (func_ov017_021d60f4() == 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    M2C_FIELD(&data_02109bf4, u8 *, 0xC8) = (u8) ((M2C_FIELD(&data_02109bf4, u8 *, 0xC8) & ~4) | ((u32) (var_r0 << 0x1F) >> 0x1D));
    return 1;
}
