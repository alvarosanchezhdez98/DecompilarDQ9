#include <m2c.h>

s32 func_ov031_0220fe44(M2C_UNK);
M2C_UNK func_ov031_0220fed8();
extern void *data_ov031_0224e580;

void func_ov031_0220f728(void) {
    void *temp_r3;

    if (func_ov031_0220fe44(0) != 0) {
        temp_r3 = M2C_FIELD(data_ov031_0224e580, void **, 0x24);
        M2C_FIELD(temp_r3, s32 *, 0x24) = (s32) *M2C_FIELD(temp_r3, s32 **, 0xC);
        M2C_FIELD(M2C_FIELD(data_ov031_0224e580, void **, 0x24), s32 *, 0x20) = 1;
    }
    func_ov031_0220fed8();
}
