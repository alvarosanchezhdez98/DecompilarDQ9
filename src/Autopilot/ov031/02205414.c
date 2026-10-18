#include <m2c.h>

s32 SOCLi_GetSizeSocket();
M2C_UNK SOCLi_InitSocket(s32, M2C_UNK);
M2C_UNK VectorizedMemset(s32, M2C_UNK, s32);
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
M2C_UNK func_ov031_022070c8(s32);
extern void *data_ov031_022496a4;

s32 SOCLi_StartupSocket(M2C_UNK arg0) {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r6;

    temp_r4 = SOCLi_GetSizeSocket();
    temp_r6 = _Z20DisableIRQInterruptsv();
    temp_r0 = M2C_FIELD(data_ov031_022496a4, s32 (**)(s32), 0x18)(temp_r4);
    if (temp_r0 != 0) {
        VectorizedMemset(temp_r0, 0, temp_r4);
        SOCLi_InitSocket(temp_r0, arg0);
        func_ov031_022070c8(temp_r0);
    }
    _Z20SetIRQInterruptStatei(temp_r6);
    return temp_r0;
}
