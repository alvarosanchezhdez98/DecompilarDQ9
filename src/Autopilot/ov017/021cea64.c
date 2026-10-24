#include <m2c.h>

s32 func_0202c1a4(s32);
M2C_UNK func_0202c5bc(s32, s32);

void func_ov017_021cea64(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r4;

    temp_r4 = M2C_FIELD(arg1, s32 *, 4);
    if (temp_r4 == func_0202c1a4(arg4)) {
        return;
    }
    func_0202c5bc(arg4, temp_r4);
}
