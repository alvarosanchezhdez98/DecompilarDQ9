#include <m2c.h>


s32 func_ov024_021f6ae8(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 8);
    if ((temp_r1 != NULL) && (((u32) (M2C_FIELD(temp_r1, u16 *, 0xA) << 0x13) >> 0x1F) != 0)) {
        M2C_FIELD(arg0, s32 *, 0x1C) = 0x40000000;
        M2C_FIELD(arg0, s32 *, 0x20) = 0x3F800000;
    } else {
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
    }
    return 1;
}
