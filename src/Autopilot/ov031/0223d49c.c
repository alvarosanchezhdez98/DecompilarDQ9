#include <m2c.h>

extern M2C_UNK data_ov031_02290d40;

s32 ov13_022417DC(void *arg0) {
    u16 temp_r2;
    u16 temp_r2_2;

    if (((s32) (*(u16 *)0x027FFFA8 & 0x8000) >> 0xF) != 0) {
        return 0;
    }
    if (((u32) (M2C_FIELD(M2C_FIELD(&data_ov031_02290d40, void **, 4), u8 *, 0x38) << 0x1E) >> 0x1F) == 0) {
        return 0;
    }
    temp_r2 = M2C_FIELD(M2C_FIELD(&data_ov031_02290d40, void **, 4), u16 *, 0x28);
    if ((u32) M2C_FIELD(arg0, u16 *, 0) > (u32) temp_r2) {
        return 0;
    }
    if ((u32) M2C_FIELD(arg0, u16 *, 4) < (u32) temp_r2) {
        return 0;
    }
    temp_r2_2 = M2C_FIELD(M2C_FIELD(&data_ov031_02290d40, void **, 4), u16 *, 0x2A);
    if ((u32) M2C_FIELD(arg0, u16 *, 2) > (u32) temp_r2_2) {
        return 0;
    }
    if ((u32) M2C_FIELD(arg0, u16 *, 6) >= (u32) temp_r2_2) {
        return 1;
    }
    return 0;
}
