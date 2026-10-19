#include <m2c.h>

M2C_UNK CPS_SocRelease();
M2C_UNK CPS_SocUnRegister();
M2C_UNK CPS_TcpClose();
M2C_UNK CPS_TcpShutdown();
M2C_UNK SOCLi_SendCommandPacket(s32, M2C_UNK);
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(s32);
M2C_UNK func_ov031_022070f0(void *);
M2C_UNK func_ov031_02207108(void *);

s32 SOCLi_CloseCallBack(void *arg0) {
    s32 temp_r5;
    s32 var_r0;
    s32 var_r1;
    s8 temp_r0;
    void *temp_r4;

    temp_r4 = M2C_FIELD(arg0, void **, 4);
    var_r1 = 1;
    temp_r0 = M2C_FIELD(temp_r4, s8 *, 0x73);
    if ((temp_r0 != 0) && (temp_r0 != 4)) {
        var_r1 = 0;
    }
    if (var_r1 != 0) {
        _Z22AwaitContextCompletionP16ProcessorContext(M2C_FIELD(temp_r4, s32 *, 0x68) + 0x20);
        CPS_TcpShutdown();
        CPS_TcpClose();
        CPS_SocRelease();
    }
    CPS_SocUnRegister();
    M2C_FIELD(temp_r4, s16 *, 0x70) = (s16) (M2C_FIELD(temp_r4, s16 *, 0x70) & ~6);
    if (M2C_FIELD(temp_r4, s8 *, 0x73) == 2) {
        var_r0 = M2C_FIELD(temp_r4, s32 *, 0x68);
    } else {
        var_r0 = M2C_FIELD(temp_r4, s32 *, 0x64);
    }
    SOCLi_SendCommandPacket(var_r0, 0);
    temp_r5 = _Z20DisableIRQInterruptsv();
    func_ov031_02207108(temp_r4);
    func_ov031_022070f0(temp_r4);
    _Z20SetIRQInterruptStatei(temp_r5);
    M2C_FIELD(temp_r4, s16 *, 0x70) = (s16) (M2C_FIELD(temp_r4, s16 *, 0x70) | 0x20);
    return 0;
}
