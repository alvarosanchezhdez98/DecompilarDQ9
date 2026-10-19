#include <m2c.h>


s32 func_02028bac(s32 arg0, s32 arg1) {
    if ((arg1 < 0) || (arg1 >= 4)) {
        return 0;
    }
    return (arg1 * 0x318) + arg0;
}
