#include <m2c.h>
#pragma optimization_level 4


u8 func_020493a4(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, u8 *, 0x1C);
    }
    return 0xFFU;
}
