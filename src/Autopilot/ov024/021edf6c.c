#include <m2c.h>

s32 func_ov000_02154a04(s32, M2C_UNK, u16, s32);

s32 func_ov024_021edf6c(s32 *arg0, M2C_UNK arg1, void *arg2, s32 *arg3, s32 arg4) {
    *arg3 = func_ov000_02154a04(*arg0, arg1, (u16) ((u32) (M2C_FIELD(arg2, s32 *, 4) << 0x14) >> 0x14), arg4);
    return 1;
}
