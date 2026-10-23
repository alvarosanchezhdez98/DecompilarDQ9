#include <m2c.h>

s32 func_020d2ff0();
s32 memcmp();
s32 sprintf();
extern M2C_UNK data_020f2dc8;
extern M2C_UNK data_020f2dcb;
extern M2C_UNK data_020f2dcf;

s32 func_020e462c(s32 arg0, s8 *arg1, M2C_UNK *arg2) {
    s32 temp_r0;
    s32 var_r0;
    s32 var_r6;

    var_r6 = arg0;
    if ((arg1 != NULL) && (*arg1 != 0)) {
        var_r6 += sprintf(arg0, &data_020f2dc8, arg1);
        if ((arg1 != NULL) && (temp_r0 = func_020d2ff0(arg1), (temp_r0 > 3))) {
            var_r0 = memcmp(&arg1[temp_r0 - 3], &data_020f2dcb, 3);
        } else {
            var_r0 = 1;
        }
        if (var_r0 != 0) {
            var_r6 += sprintf(var_r6, &data_020f2dcf);
        }
    }
    return var_r6 + sprintf(var_r6, arg2);
}
