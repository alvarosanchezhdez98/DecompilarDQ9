#include <m2c.h>

s32 func_ov001_021641e0(s32, M2C_UNK, M2C_UNK, s32);

s32 func_ov001_02164248(s32 arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    if ((arg1 < 0) || (arg1 >= 0x20)) {
        return 0;
    }
    return func_ov001_021641e0(arg0 + (arg1 * 0x10), arg2, arg3, arg4);
}
