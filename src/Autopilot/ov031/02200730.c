#include <m2c.h>

s32 ip_islocal();
extern M2C_UNK data_ov031_0224c980;

s32 get_targetip(s32 arg0) {
    s32 var_r4;

    var_r4 = arg0;
    if (ip_islocal() == 0) {
        var_r4 = M2C_FIELD(&data_ov031_0224c980, s32 *, 0x2C);
    }
    return var_r4;
}
