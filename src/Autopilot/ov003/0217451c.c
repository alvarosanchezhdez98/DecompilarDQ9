#include <m2c.h>

M2C_UNK func_02081ea4(s32, s16, M2C_UNK);

void func_ov003_0217451c(void *arg0) {
    s16 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s16 *, 0xFFC);
    if ((s32) temp_r1 < 0) {
        return;
    }
    func_02081ea4(M2C_FIELD(arg0, s32 *, 0x89C), temp_r1, 1);
    M2C_FIELD(arg0, s16 *, 0xFFC) = -1;
}
