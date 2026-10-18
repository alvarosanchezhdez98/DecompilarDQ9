#include <m2c.h>

M2C_UNK WCMi_ResetKeepAliveAlarm();
M2C_UNK _Z15UnblockContextsP18BlockedContextList(M2C_UNK *);
extern M2C_UNK data_ov031_0224e540;
extern M2C_UNK data_ov031_0224e544;

void WcmCpsifWmCallback(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0) != 0x12) {
        return;
    }
    M2C_FIELD(&data_ov031_0224e540, s32 *, 0x24) = (s32) M2C_FIELD(arg0, u16 *, 2);
    if (M2C_FIELD(arg0, u16 *, 2) == 0) {
        WCMi_ResetKeepAliveAlarm();
    }
    _Z15UnblockContextsP18BlockedContextList(&data_ov031_0224e544);
}
