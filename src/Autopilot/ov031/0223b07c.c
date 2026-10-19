#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
extern void *data_ov031_02290d20;

void ov13_0223F3BC(void) {
    VectorizedMemset(data_ov031_02290d20 + 0x100, 0, 0x100);
    VectorizedMemset(data_ov031_02290d20, 0, 0x100);
    M2C_FIELD(data_ov031_02290d20, void **, 0xAB0) = (void *) data_ov031_02290d20;
}
