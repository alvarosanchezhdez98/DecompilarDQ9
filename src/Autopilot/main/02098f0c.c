#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32, s32, M2C_UNK);

void func_02098efc(s32 arg0, s32 arg1, s32 arg2, M2C_UNK arg3) {
    if (arg2 == 0) {
        return;
    }
    VectorizedInvertedMemcpy(arg2, arg0 + arg1, arg3);
}
