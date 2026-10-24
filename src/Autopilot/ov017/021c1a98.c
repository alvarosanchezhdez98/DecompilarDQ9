#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_020469b4(s32, void *);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021c1acc(void *);

void func_ov017_021c1a98(s32 arg0, s32 arg1) {
    s32 temp_r4;
    void *temp_r0;
    void *temp_r5;

    temp_r0 = func_ov017_0218b5b0();
    temp_r5 = M2C_FIELD(temp_r0, void **, 0x3B78);
    temp_r4 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    func_ov017_021c1acc(temp_r5);
    M2C_FIELD(temp_r5, s32 *, 0xC) = arg1;
    func_020469b4(temp_r4, temp_r5);
}
