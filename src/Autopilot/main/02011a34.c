#include <m2c.h>
#pragma optimization_level 4

M2C_UNK VectorizedInvertedMemcpy(M2C_UNK, s32, M2C_UNK);

void func_02011a24(s32 arg0, M2C_UNK arg1) {
    VectorizedInvertedMemcpy(arg1, arg0 + 0x6482, 0x1C);
}
