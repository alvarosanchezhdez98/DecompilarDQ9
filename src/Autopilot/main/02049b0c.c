#include <m2c.h>


s32 func_02049afc(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x13C);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (M2C_FIELD(temp_r0, u8 *, 0x4F) != 0) {
        return 1;
    }
    return 0;
}
