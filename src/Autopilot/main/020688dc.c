#include <m2c.h>


s32 func_020688cc(s32 arg0, void *arg1) {
    if (M2C_FIELD(arg1, u8 *, 0x19D5) == 0) {
        return 1;
    }
    return 0;
}
