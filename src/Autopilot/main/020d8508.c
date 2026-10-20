#include <m2c.h>

M2C_UNK VectorizedMemset(M2C_UNK, M2C_UNK, s32);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(M2C_UNK, s32);

s32 func_020d84f8(M2C_UNK arg0, s32 arg1) {
    VectorizedMemset(arg0, 0, arg1);
    _Z25CleanInvalidateCacheRangePKvj(arg0, arg1);
    return arg1;
}
