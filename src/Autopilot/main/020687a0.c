#include <m2c.h>
#pragma optimization_level 4


s32 func_02068790(s32 arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0x8B8) != 1) {
        return 1;
    }
    return 0;
}
