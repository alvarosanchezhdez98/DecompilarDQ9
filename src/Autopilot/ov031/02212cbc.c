#include <m2c.h>

s32 DWC_Auth_CheckPseudoWiFiID();
s32 DWC_BM_Init(M2C_UNK);
M2C_UNK DWCi_AUTH_MakeWiFiID(M2C_UNK);
M2C_UNK func_02000b9c(s32);

s32 DWC_Init(M2C_UNK arg0) {
    s32 temp_r4;
    s32 var_r0;
    s32 var_r5;

    var_r5 = 0;
    func_02000b9c(0x02000C5C);
    temp_r4 = DWC_BM_Init(arg0);
    if (DWC_Auth_CheckPseudoWiFiID() != 0) {
        DWCi_AUTH_MakeWiFiID(arg0);
        var_r5 = 1;
    }
    if (temp_r4 < 0) {
        if (var_r5 != 0) {
            var_r0 = 2;
        } else {
            var_r0 = 3;
        }
        return var_r0;
    }
    if (var_r5 != 0) {
        return 1;
    }
    return 0;
}
