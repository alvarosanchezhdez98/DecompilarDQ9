#include <m2c.h>


s32 func_ov003_02155e14(s32 arg0, s32 arg1) {
    if ((arg1 <= 0) || (arg1 >= 0xD)) {
        return 0;
    }
    return arg0 + ((arg1 - 1) * 0x10);
}
