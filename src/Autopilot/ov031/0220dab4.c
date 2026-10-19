#include <m2c.h>

M2C_UNK _Z10SetTimeoutP5AlarmyPFvPP16ProcessorContextES3_(void *, s32, M2C_UNK, M2C_UNK *, s32);
M2C_UNK _Z11CancelAlarmP5Alarm(void *);
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
extern void *data_ov031_0224e53c;
extern M2C_UNK func_ov031_0220db28;

void WCMi_ResetKeepAliveAlarm(void) {
    s32 temp_r4;

    temp_r4 = _Z20DisableIRQInterruptsv();
    _Z11CancelAlarmP5Alarm(data_ov031_0224e53c + 0x22CC);
    if (M2C_FIELD(data_ov031_0224e53c, s32 *, 0x2260) == 9) {
        _Z10SetTimeoutP5AlarmyPFvPP16ProcessorContextES3_(data_ov031_0224e53c + 0x22CC, 0x022F5341, 0, &func_ov031_0220db28, 0);
    }
    _Z20SetIRQInterruptStatei(temp_r4);
}
