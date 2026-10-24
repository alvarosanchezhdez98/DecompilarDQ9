#include <m2c.h>


s32 func_ov024_021eb4b0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 & 8) {
        return 0;
    }
    if (arg1 & 0x10) {
        return 0;
    }
    if (arg1 & 0x80000) {
        return 0;
    }
    if (!(arg1 & arg2)) {
        return 1;
    }
    return 0;
}
