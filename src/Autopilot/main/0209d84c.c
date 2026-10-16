#include <m2c.h>

s32 func_ov017_021d60f4(s32);
s32 func_02094d6c();
void *func_02096134(s32, s32);
s32 func_0209dccc();

s32 func_0209d83c(s32 arg0) {
    s32 temp_r0;
    s32 var_r0;
    void *temp_r0_2;

    temp_r0 = func_02094d6c();
    if (temp_r0 == 0) {
        return 0;
    }
    if (func_0209dccc() == 0) {
        return 0;
    }
    temp_r0_2 = func_02096134(temp_r0, func_ov017_021d60f4(arg0));
    if (temp_r0_2 == NULL) {
        return 0;
    }
    var_r0 = func_ov017_021d60f4(arg0 + 8);
    if (var_r0 > 0xFFFF) {
        var_r0 = 0xFFFF;
    }
    M2C_FIELD(temp_r0_2, s16 *, 0xA) = (s16) var_r0;
    return 1;
}
