#include <m2c.h>


s32 func_ov024_021f6bf0(void *arg0) {
    void *temp_r0;

    temp_r0 = M2C_FIELD(arg0, void **, 8);
    if ((temp_r0 != NULL) && (((u32) (M2C_FIELD(temp_r0, u16 *, 0xA) << 0x15) >> 0x1C) == 1)) {
        M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (1.5f * M2C_FIELD(arg0, f32 *, 0x14));
        M2C_FIELD(arg0, f32 *, 0x20) = (f32) (1.5f * M2C_FIELD(arg0, f32 *, 0x18));
    }
    return 1;
}
