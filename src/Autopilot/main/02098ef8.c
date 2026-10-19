#include <m2c.h>


u8 func_02098ee8(void *arg0) {
    u8 temp_r0;

    temp_r0 = M2C_FIELD(arg0, u8 *, 0x1B61);
    M2C_FIELD(arg0, u8 *, 0x1B61) = 0U;
    return temp_r0;
}
