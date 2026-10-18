#include <m2c.h>

M2C_UNK func_0203ac40(void *, s16, M2C_UNK, M2C_UNK);

void func_0205eb90(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s16 *, 0xC4);
    if ((s32) temp_r1 < 0) {
        return;
    }
    func_0203ac40(arg0, temp_r1, arg1, arg2);
}
