#include <m2c.h>


s32 func_ov017_021b1ffc(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x24);
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, s32 *, 0x394);
    }
    return 0;
}
