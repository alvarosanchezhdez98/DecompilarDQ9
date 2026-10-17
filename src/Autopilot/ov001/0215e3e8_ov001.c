#include <m2c.h>
#pragma optimization_level 4

void *func_020421a0();
M2C_UNK func_ov017_021d6134(M2C_UNK, s32);

s32 func_ov001_0215e3e8(M2C_UNK arg0) {
    void *temp_r0;

    temp_r0 = func_020421a0();
    if (temp_r0 == NULL) {
        return 0;
    }
    func_ov017_021d6134(arg0, M2C_FIELD(temp_r0, s32 *, 0x9A0));
    return 1;
}
