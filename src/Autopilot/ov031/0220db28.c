#include <m2c.h>

M2C_UNK WCMi_CpsifSendNullPacket();
M2C_UNK WCMi_ResetKeepAliveAlarm();

void func_ov031_0220db28(void) {
    WCMi_CpsifSendNullPacket();
    WCMi_ResetKeepAliveAlarm();
}
