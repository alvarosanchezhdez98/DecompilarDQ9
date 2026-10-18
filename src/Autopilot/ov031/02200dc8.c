#include <m2c.h>

M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
s32 inq_arpcache(M2C_UNK);
M2C_UNK send_arprequest(M2C_UNK);
extern M2C_UNK data_ov031_0224c980;

s32 arprequest(M2C_UNK arg0) {
    s32 temp_r0;
    u32 var_r7;
    u32 var_r8;

    var_r7 = 0;
loop_1:
    send_arprequest(arg0);
    var_r8 = 0;
loop_2:
    if (M2C_FIELD(&data_ov031_0224c980, s32 *, 0x50) == 0) {
        return 0;
    }
    _Z19SleepCurrentContextj(0x64);
    temp_r0 = inq_arpcache(arg0);
    if (temp_r0 != 0) {
        return temp_r0;
    }
    var_r8 += 1;
    if (var_r8 >= 0x14U) {
        var_r7 += 1;
        if (var_r7 >= 8U) {
            return 0;
        }
        goto loop_1;
    }
    goto loop_2;
}
