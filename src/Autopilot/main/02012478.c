#include <m2c.h>


s32 func_02012468(void *arg0, s32 arg1) {
    if (!(M2C_FIELD(arg0, u16 *, 0) & arg1) && (M2C_FIELD(arg0, u16 *, 2) & arg1)) {
        return 1;
    }
    return 0;
}
