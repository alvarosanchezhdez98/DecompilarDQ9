#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, s32);
void *func_ov017_0218b5b0();

void func_ov004_0216342c(void *arg0) {
    void *temp_r4;

    temp_r4 = func_ov017_0218b5b0();
    VectorizedMemset(arg0, 0, 0x1914);
    M2C_FIELD(arg0, u8 *, 0x18FA) = (u8) M2C_FIELD(temp_r4, u8 *, 0x42E0);
    M2C_FIELD(arg0, s8 *, 0x18FB) = 0;
    M2C_FIELD(arg0, s8 *, 0x18FC) = 0;
    M2C_FIELD(arg0, s8 *, 0x18FD) = 0;
    M2C_FIELD(arg0, s8 *, 0x18FE) = 0;
}
