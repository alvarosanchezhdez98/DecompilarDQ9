#include <m2c.h>


s32 func_0209372c(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 0x2710)) {
        return 0;
    }
    if ((arg0 >= 0x2710) && (arg0 < 0x4E20)) {
        return 1;
    }
    if ((arg0 >= 0x4E20) && (arg0 < 0x7530)) {
        return 2;
    }
    return 3;
}
