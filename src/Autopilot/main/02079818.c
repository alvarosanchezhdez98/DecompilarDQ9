#include <m2c.h>

s32 func_02079840(M2C_UNK, s32, M2C_UNK);

s32 func_02079808(M2C_UNK arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = func_02079840(arg0, M2C_FIELD(arg1, s32 *, 0), 0);
    M2C_FIELD(arg1, s32 *, 0x34) = func_02079840(arg0, M2C_FIELD(arg1, s32 *, 0x34), 0);
    return 1;
}
