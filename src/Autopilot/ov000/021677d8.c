#include <m2c.h>


s32 func_ov000_021677d8(s32 arg0, s32 arg1) {
    if ((arg1 >= 0) && (arg1 < 4)) {
        return arg0 + 0x5910 + (arg1 * 0x10);
    }
    return 0;
}
