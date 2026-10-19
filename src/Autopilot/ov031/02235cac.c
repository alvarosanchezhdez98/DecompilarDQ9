#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(M2C_UNK, void *, M2C_UNK);
extern void *data_ov031_02290cfc;

void ov13_0223A02C(M2C_UNK arg0) {
    VectorizedInvertedMemcpy(arg0, data_ov031_02290cfc + 0x440, 0x20);
    M2C_FIELD(data_ov031_02290cfc, s8 *, 0x4E7) = 0;
}
