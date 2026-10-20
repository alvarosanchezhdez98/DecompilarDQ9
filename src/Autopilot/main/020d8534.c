#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(M2C_UNK, s32);

s32 func_020d8524(M2C_UNK arg0, M2C_UNK arg1, s32 arg2) {
    VectorizedInvertedMemcpy(arg1, arg0);
    _Z25CleanInvalidateCacheRangePKvj(arg0, arg2);
    return arg2;
}
