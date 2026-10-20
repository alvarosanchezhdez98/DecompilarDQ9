#include <m2c.h>

M2C_UNK func_0203ac40(void *, s16, s16, M2C_UNK);

void func_0203aa08(void *arg0) {
    s16 temp_r1;

    if (M2C_FIELD(arg0, s32 *, 0) == 0) {
        return;
    }
    temp_r1 = M2C_FIELD(arg0, s16 *, 0xAC);
    if ((s32) temp_r1 < 0) {
        return;
    }
    func_0203ac40(arg0, temp_r1, M2C_FIELD(arg0, s16 *, 0xAE), 0);
    M2C_FIELD(arg0, s16 *, 0xAC) = -1;
    M2C_FIELD(arg0, s16 *, 0xAE) = -1;
}
