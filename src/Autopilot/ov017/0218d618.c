#include <m2c.h>


s32 func_ov017_0218d618(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x4498);
    if ((temp_r0 == NULL) || (M2C_FIELD(temp_r0, s32 *, 0x10) != 2)) {
        return 0;
    }
    return 1;
}
