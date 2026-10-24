#include <m2c.h>

s32 func_ov000_02156068(s32, s16, M2C_UNK, M2C_UNK);

s32 func_ov024_021d8f4c(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (func_ov000_02156068(*arg0, arg2, 0xC, 0) == 0) {
        return arg5;
    }
    return (s32) (1.5f * (f32) arg5);
}
