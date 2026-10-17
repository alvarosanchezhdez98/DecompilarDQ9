#include <m2c.h>

M2C_UNK func_0205d6a0(s32, M2C_UNK);
M2C_UNK func_0205dee8(s32, M2C_UNK);

void func_ov003_0216ff90(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x3C);
    if (temp_r0 == 0) {
        return;
    }
    func_0205dee8(temp_r0, 0);
    func_0205d6a0(M2C_FIELD(arg0, s32 *, 0x3C), 0);
}
