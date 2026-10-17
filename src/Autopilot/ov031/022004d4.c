#include <m2c.h>

s32 _Z17IsContextInactiveP16ProcessorContext(M2C_UNK *);
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
M2C_UNK _Z25MarkContextReadyAndSwitchP16ProcessorContext(M2C_UNK *);
extern M2C_UNK data_ov031_0224c980;
extern M2C_UNK data_ov031_0224cb28;

s32 CPS_CalmDown(void) {
    s32 var_r4;
    s32 var_r5;

    var_r4 = _Z20DisableIRQInterruptsv();
    var_r5 = _Z17IsContextInactiveP16ProcessorContext(&data_ov031_0224cb28);
    if ((var_r5 == 0) && (M2C_FIELD(&data_ov031_0224c980, s32 *, 0x44) == 0)) {
        M2C_FIELD(&data_ov031_0224c980, s32 *, 0x44) = 1;
        _Z25MarkContextReadyAndSwitchP16ProcessorContext(&data_ov031_0224cb28);
    }
    _Z20SetIRQInterruptStatei(var_r4);
    return var_r5;
}
