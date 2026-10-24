#include <m2c.h>
#pragma optimization_level 4

void *func_ov017_021b8478(s32);
M2C_UNK func_ov017_021b86e0(s32);

void func_ov017_021cbc0c(s32 arg0, void *arg1, s32 arg2, void *arg3) {
    s32 temp_r4;
    void *temp_r0;

    temp_r4 = M2C_FIELD(arg3, s32 *, 0x3718);
    temp_r0 = func_ov017_021b8478(temp_r4);
    if (temp_r0 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r0, u16 *, 8) != M2C_FIELD(arg1, u16 *, 4)) {
        return;
    }
    func_ov017_021b86e0(temp_r4);
}
