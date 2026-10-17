#include <m2c.h>


s32 func_ov017_0218d75c(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x4498);
    if ((temp_r0 != NULL) && (M2C_FIELD(temp_r0, u8 *, 0x14) != 0)) {
        return 1;
    }
    return 0;
}
