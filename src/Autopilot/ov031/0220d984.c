#include <m2c.h>

M2C_UNK WcmNotifyEx(s16, M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern void *data_ov031_0224e53c;

void WcmNotify(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    s16 temp_r0;

    temp_r0 = M2C_FIELD(data_ov031_0224e53c, s16 *, 0x2280);
    M2C_FIELD(data_ov031_0224e53c, s16 *, 0x2280) = 0;
    WcmNotifyEx(temp_r0, arg0, arg1, arg2, arg3);
}
