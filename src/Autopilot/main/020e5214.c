#include <m2c.h>

s32 func_020e523c(M2C_UNK, s32, M2C_UNK);

s32 func_020e5204(M2C_UNK arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = func_020e523c(arg0, M2C_FIELD(arg1, s32 *, 0), 0);
    M2C_FIELD(arg1, s32 *, 4) = func_020e523c(arg0, M2C_FIELD(arg1, s32 *, 4), 0);
    return 1;
}
