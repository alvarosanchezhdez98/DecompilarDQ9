#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32, s32, M2C_UNK);

u8 func_020119f8(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        VectorizedInvertedMemcpy(arg0 + 0x6482, arg1, 0x1C);
    }
    return M2C_FIELD(arg0, u8 *, 0x6480);
}
