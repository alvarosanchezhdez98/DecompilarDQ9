#include <m2c.h>

extern void *data_ov031_022496a4;
extern s32 data_ov031_0224c99c;
extern s32 data_ov031_0224c9ac;
extern s32 data_ov031_0224c9d0;
extern M2C_UNK data_ov031_0224c9e0;
extern M2C_UNK data_ov031_0224e1c0;

void SOCLi_SetMyIP(void) {
    data_ov031_0224c9d0 = M2C_FIELD(data_ov031_022496a4, s32 *, 4);
    data_ov031_0224c99c = M2C_FIELD(data_ov031_022496a4, s32 *, 8);
    data_ov031_0224c9ac = M2C_FIELD(data_ov031_022496a4, s32 *, 0xC);
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 0) = (s32) M2C_FIELD(data_ov031_022496a4, s32 *, 0x10);
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 4) = (s32) M2C_FIELD(data_ov031_022496a4, s32 *, 0x14);
    M2C_FIELD(&data_ov031_0224e1c0, s32 *, 8) = (s32) (M2C_FIELD(&data_ov031_0224e1c0, s32 *, 8) | 2);
}
