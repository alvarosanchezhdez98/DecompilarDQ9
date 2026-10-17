#include <m2c.h>
#pragma optimization_level 4


s32 func_020120a0(s32 arg0, u32 arg1) {
    if (arg1 < 4U) {
        return arg0 + 0x74DE + (arg1 * 8);
    }
    return 0;
}
