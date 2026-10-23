#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(M2C_UNK *, s32, M2C_UNK);
s32 WCM_SendDCFDataEx(s32, s32, s32, M2C_UNK, s32);
extern M2C_UNK data_ov031_0224968c;
extern s8 data_ov031_0224c980;

void send_packet(s32 arg0, s32 arg1, M2C_UNK arg2, s32 arg3) {
    s8 var_r1;

    VectorizedInvertedMemcpy(&data_ov031_0224968c, arg0 + 6, 6);
    if (WCM_SendDCFDataEx(arg0, arg0 + 6, arg1 - 6, arg2, arg3) < 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    data_ov031_0224c980 = var_r1;
}
