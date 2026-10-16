#include <m2c.h>


s32 func_ov025_021e8cf0(s32 arg0, s32 arg1) {
    if ((arg1 < 0) || (arg1 >= 0x10)) {
        return 0;
    }
    return arg0 + 0x1DC + (arg1 * 4);
}
