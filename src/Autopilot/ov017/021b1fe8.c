#include <m2c.h>


u8 func_ov017_021b1fe8(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x24);
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, u8 *, 0x44);
    }
    return 0U;
}
