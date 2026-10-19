#include <m2c.h>

s32 func_020dfbfc(M2C_UNK, s32, M2C_UNK);

s32 func_020dfbdc(M2C_UNK arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 4) = func_020dfbfc(arg0, M2C_FIELD(arg1, s32 *, 4), 0);
    return 1;
}
