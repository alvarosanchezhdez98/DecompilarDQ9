#include <m2c.h>

extern void *data_ov031_0224e580;

void func_ov031_0220fdec(s32 arg0, s32 *arg1) {
    s32 (*temp_r2)(s32 *);
    s32 var_r3;

    var_r3 = 1;
    if ((arg0 >= 0) && ((u32) arg0 >= 0xCU) && (*arg1 == arg0)) {
        temp_r2 = M2C_FIELD(data_ov031_0224e580, s32 (**)(s32 *), 0x28);
        if (temp_r2 != NULL) {
            var_r3 = temp_r2(arg1);
        }
    }
    M2C_FIELD(data_ov031_0224e580, s32 *, 0x2C) = var_r3;
}
