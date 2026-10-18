#include <m2c.h>

s32 CPS_Resolve(M2C_UNK);
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
extern M2C_UNK data_ov031_0224c9e0;

s32 SOCL_InetAtoH(M2C_UNK arg0) {
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;

    temp_r5 = _Z20DisableIRQInterruptsv();
    temp_r6 = M2C_FIELD(&data_ov031_0224c9e0, s32 *, 0);
    temp_r7 = M2C_FIELD(&data_ov031_0224c9e0, s32 *, 4);
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 0) = 0;
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 4) = 0;
    temp_r4 = CPS_Resolve(arg0);
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 0) = temp_r6;
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 4) = temp_r7;
    _Z20SetIRQInterruptStatei(temp_r5);
    return temp_r4;
}
