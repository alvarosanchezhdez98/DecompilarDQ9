#include <m2c.h>

M2C_UNK func_0202e9a4(s32, s32);
s32 func_ov000_02160130();
s32 func_ov000_02160f14();

s32 func_ov025_021e8510(void *arg0) {
    s32 temp_r0;

    if (func_ov000_02160130() == 0) {
        return 1;
    }
    temp_r0 = func_ov000_02160f14();
    if (temp_r0 == 0) {
        return 1;
    }
    func_0202e9a4(temp_r0, M2C_FIELD(arg0, s32 *, 8));
    return 1;
}
