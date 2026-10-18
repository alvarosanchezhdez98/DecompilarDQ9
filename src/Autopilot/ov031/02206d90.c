#include <m2c.h>

s32 CPS_CalmDown();
M2C_UNK SOCL_Close(s32);
s32 SOCL_CloseAll();
s32 SOCL_IsClosed(s32);
M2C_UNK SOCLi_TrashSocket();
M2C_UNK WCM_SetRecvDCFCallback(M2C_UNK);
extern s32 data_ov031_0224e1cc;

s32 SOCL_CalmDown(void) {
    s32 var_r4;

    if (data_ov031_0224e1cc != 0) {
        var_r4 = SOCL_CloseAll();
        if (var_r4 == 0) {
            SOCL_Close(data_ov031_0224e1cc);
            if (SOCL_IsClosed(data_ov031_0224e1cc) != 0) {
                data_ov031_0224e1cc = 0;
            }
            var_r4 = -0x1A;
        }
        SOCLi_TrashSocket();
    } else if (CPS_CalmDown() == 0) {
        var_r4 = -0x1A;
    } else {
        WCM_SetRecvDCFCallback(0);
        var_r4 = 0;
    }
    return var_r4;
}
