#include <m2c.h>

M2C_UNK func_ov000_02163d94();
s32 func_ov017_021b8468(s32);
void *func_ov017_021b8478(s32);

void func_ov017_021cc080(s32 arg0, void *arg1, s32 arg2, void *arg3) {
    s32 temp_r0;
    s32 temp_r5;
    void *temp_r4;

    temp_r5 = M2C_FIELD(arg3, s32 *, 0x3718);
    temp_r4 = func_ov017_021b8478(temp_r5);
    temp_r0 = func_ov017_021b8468(temp_r5);
    if (temp_r4 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r4, u16 *, 8) != M2C_FIELD(arg1, u16 *, 4)) {
        return;
    }
    if (temp_r0 == 0) {
        return;
    }
    func_ov000_02163d94();
}
