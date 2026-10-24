#include <m2c.h>


u32 func_020688b0(s32 arg0, void *arg1) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg1, void **, 0x10);
    if (temp_r0 != NULL) {
        return (u32) (M2C_FIELD(temp_r0, s32 *, 8) << 6) >> 0x1E;
    }
    return 0U;
}
