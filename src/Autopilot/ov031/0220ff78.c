#include <m2c.h>

extern void *data_ov031_0224e580;

s32 func_ov031_0220ff78(void *arg0) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 8);
    switch (temp_r1) {                              /* irregular */
    case 0xC9:
        M2C_FIELD(M2C_FIELD(data_ov031_0224e580, void **, 0x24), s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
        M2C_FIELD(M2C_FIELD(data_ov031_0224e580, void **, 0x24), s32 *, 0x20) = 1;
        break;
    case 0xCA:
        if ((u32) (M2C_FIELD(arg0, s32 *, 0xC) - 2) <= 1U) {
            M2C_FIELD(M2C_FIELD(data_ov031_0224e580, void **, 0x24), s32 *, 0x24) = 0;
            M2C_FIELD(M2C_FIELD(data_ov031_0224e580, void **, 0x24), s32 *, 0x20) = 1;
        }
        break;
    }
    return 1;
}
