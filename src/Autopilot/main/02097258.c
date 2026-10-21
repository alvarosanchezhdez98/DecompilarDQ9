#include <m2c.h>

s32 func_02097280(M2C_UNK, s32, M2C_UNK);

s32 func_02097248(M2C_UNK arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 4) = func_02097280(arg0, M2C_FIELD(arg1, s32 *, 4), 0);
    M2C_FIELD(arg1, s32 *, 8) = func_02097280(arg0, M2C_FIELD(arg1, s32 *, 8), 0);
    return 1;
}
