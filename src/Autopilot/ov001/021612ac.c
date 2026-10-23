#include <m2c.h>


u32 func_ov001_021612ac(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 0x150);
    if (temp_r0 != NULL) {
        return (u32) (M2C_FIELD(temp_r0, u8 *, 0x56B) << 0x1C) >> 0x1C;
    }
    return 0U;
}
