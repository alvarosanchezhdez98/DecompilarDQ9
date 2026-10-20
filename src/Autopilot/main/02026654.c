#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);

void func_02026644(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x12) != 0) {
        M2C_FIELD(arg0, s8 *, 0x779) = 0;
        M2C_FIELD(arg0, s8 *, 0x9BA) = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x780) = 0;
    VectorizedMemset(arg0 + 0x784, 0, 0x230);
}
