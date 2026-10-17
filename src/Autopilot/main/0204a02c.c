#include <m2c.h>
#pragma optimization_level 4


s32 func_0204a01c(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, s32 *, 0x68);
    }
    return 0;
}
