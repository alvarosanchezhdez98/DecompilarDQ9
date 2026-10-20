#include <m2c.h>

M2C_UNK func_0203cea4(s32);
M2C_UNK func_02041538();

void func_02040bcc(void *arg0) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r1 != 0) {
        func_0203cea4(temp_r1);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x18) == 0) {
        return;
    }
    func_02041538();
}
