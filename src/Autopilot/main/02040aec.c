#include <m2c.h>


s16 func_02040adc(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x14);
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, s16 *, 0x2E);
    }
    return 0x3D;
}
