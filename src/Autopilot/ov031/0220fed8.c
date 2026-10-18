#include <m2c.h>

M2C_UNK func_ov031_02210314(M2C_UNK);
extern void *data_ov031_0224e580;

void func_ov031_0220fed8(void) {
    if (data_ov031_0224e580 == NULL) {
        return;
    }
    func_ov031_02210314(0);
    M2C_FIELD(data_ov031_0224e580, s32 *, 0x28) = 0;
    M2C_FIELD(data_ov031_0224e580, s32 *, 0x2C) = 1;
}
