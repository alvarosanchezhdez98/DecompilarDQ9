#include <m2c.h>


void func_ov003_0215385c(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x5A) == 0) {
        M2C_FIELD(arg0, u8 *, 0x5A) = 0U;
        M2C_FIELD(arg0, s8 *, 0x5B) = 0;
    }
}
