#include <m2c.h>

void *ov00_021EC264(s32);
extern M2C_UNK (*data_ov031_0224e5ac)(M2C_UNK, void *, s32);

void ov00_021EC2EC(M2C_UNK arg0, s32 arg1) {
    void *temp_r0;

    if (arg1 == 0) {
        return;
    }
    temp_r0 = ov00_021EC264(arg1);
    data_ov031_0224e5ac(arg0, temp_r0, M2C_FIELD(temp_r0, s32 *, 4) + 0x20);
}
