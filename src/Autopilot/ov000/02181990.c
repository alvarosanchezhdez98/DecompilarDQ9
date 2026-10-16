#include <m2c.h>

s32 *func_ov025_021e8cf0(s32, M2C_UNK);
extern s32 data_ov025_021ef994;

s32 func_ov000_02181990(M2C_UNK arg0, s32 *arg1) {
    s32 *temp_r0;

    temp_r0 = func_ov025_021e8cf0(data_ov025_021ef994, arg0);
    if (temp_r0 == NULL) {
        return 0;
    }
    *arg1 = *temp_r0;
    return 1;
}
