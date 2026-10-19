#include <m2c.h>

s32 WcmCpsifTryLockMutexInIRQ(M2C_UNK *);
M2C_UNK WcmCpsifUnlockMutexInIRQ(M2C_UNK *);
s32 func_020d5bfc(M2C_UNK *, void *, void *, M2C_UNK);
void *func_ov031_0220d60c();
extern M2C_UNK data_ov031_0224e54c;
extern M2C_UNK func_ov031_0220f2cc;

void WCMi_CpsifSendNullPacket(void) {
    void *temp_r0;

    temp_r0 = func_ov031_0220d60c();
    if (temp_r0 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r0, s32 *, 0x2260) != 9) {
        return;
    }
    if (M2C_FIELD(temp_r0, u8 *, 0x226B) == 1) {
        return;
    }
    if (WcmCpsifTryLockMutexInIRQ(&data_ov031_0224e54c) == 0) {
        return;
    }
    if (func_020d5bfc(&func_ov031_0220f2cc, temp_r0 + 0x2144, temp_r0 + 0xF00, 0) == 2) {
        return;
    }
    WcmCpsifUnlockMutexInIRQ(&data_ov031_0224e54c);
}
