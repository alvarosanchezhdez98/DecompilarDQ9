#include <m2c.h>

M2C_UNK func_020c7fe0(void *, void *, M2C_UNK);
extern void *data_ov031_0224e580;

void func_ov031_0220f68c(void) {
    void *temp_r1;

    func_020c7fe0(data_ov031_0224e580, data_ov031_0224e580 + 0x24, 1);
    temp_r1 = M2C_FIELD(data_ov031_0224e580, void **, 0x24);
    if (temp_r1 == NULL) {
        return;
    }
    M2C_FIELD(temp_r1, s32 *, 0x1C) = 0;
    M2C_FIELD(M2C_FIELD(data_ov031_0224e580, void **, 0x24), s32 *, 0x20) = 0;
    M2C_FIELD(M2C_FIELD(data_ov031_0224e580, void **, 0x24), s32 *, 0x24) = 0;
}
