#include <m2c.h>

M2C_UNK VectorizedMemset(s32, M2C_UNK, s32);
extern void *data_ov031_0224e53c;

void WcmConfigure(void *arg0, s32 arg1) {
    s32 temp_r3;

    if (arg0 == NULL) {
        M2C_FIELD(data_ov031_0224e53c, s32 *, 0x226C) = 3;
        M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2270) = 0;
        M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2274) = 0;
        M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2278) = 0;
    } else {
        M2C_FIELD(data_ov031_0224e53c, s32 *, 0x226C) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 3);
        temp_r3 = M2C_FIELD(arg0, s32 *, 4);
        if ((u32) (((4 - (temp_r3 & 3)) & 3) + 0xC) > (u32) M2C_FIELD(arg0, u32 *, 8)) {
            M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2270) = 0;
            M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2274) = 0;
        } else {
            M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2270) = (s32) ((temp_r3 + 3) & ~3);
            M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2274) = (s32) (M2C_FIELD(arg0, u32 *, 8) - ((4 - (M2C_FIELD(arg0, s32 *, 4) & 3)) & 3));
            VectorizedMemset(M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2270), 0, M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2274));
        }
        M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2278) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    }
    M2C_FIELD(data_ov031_0224e53c, s32 *, 0x227C) = arg1;
}
