#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32);

void func_0200fd14(s32 *arg0, s32 arg1, s32 arg2) {
    VectorizedInvertedMemcpy(*arg0);
    *arg0 += arg2;
}
