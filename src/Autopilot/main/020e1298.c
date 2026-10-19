#include <m2c.h>


s32 func_020e1288(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 8);
    if (temp_r0 != NULL) {
        return (s32) (M2C_FIELD(temp_r0, u8 *, 0xA) * M2C_FIELD(temp_r0, u8 *, 0xB)) >> 1;
    }
    return 0;
}
