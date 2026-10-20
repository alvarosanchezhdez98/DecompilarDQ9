#include <m2c.h>

M2C_UNK func_0203a46c(void *, s32, s32, M2C_UNK);

void func_ov017_0219b578(void *arg0, s32 arg1, s32 arg2) {
    void *temp_r6;

    temp_r6 = M2C_FIELD(arg0, void **, 0x3630);
    if (temp_r6 == NULL) {
        return;
    }
    func_0203a46c(temp_r6, (s32) (4096.0f * (((f32) M2C_FIELD(temp_r6, s32 *, 0x1C) / 4096.0f) + (f32) arg1)), (s32) (4096.0f * (((f32) M2C_FIELD(temp_r6, s32 *, 0x20) / 4096.0f) + (f32) arg2)), 0);
}
