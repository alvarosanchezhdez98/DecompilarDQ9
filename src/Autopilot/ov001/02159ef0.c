#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_ov001_02159cfc(void *);

s32 func_ov001_02159ef0(s32 arg0, void *arg1) {
    s32 temp_r4;

    if (arg1 == NULL) {
        return 0;
    }
    temp_r4 = M2C_FIELD(arg1, s32 *, 0x3C);
    func_ov001_02159cfc(arg1);
    return temp_r4;
}
