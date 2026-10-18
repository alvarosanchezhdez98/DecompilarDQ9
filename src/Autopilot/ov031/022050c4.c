#include <m2c.h>

extern void *data_ov031_022496a4;
extern M2C_UNK data_ov031_0224e200;

s32 SOCLi_CleanupCommandPacketQueue(void) {
    if ((s32) M2C_FIELD(&data_ov031_0224e200, s32 *, 0x20) < (s32) M2C_FIELD(&data_ov031_0224e200, s32 *, 0x18)) {
        return -1;
    }
    M2C_FIELD(data_ov031_022496a4, M2C_UNK (**)(s32), 0x1C)(M2C_FIELD(&data_ov031_0224e200, s32 *, 0));
    M2C_FIELD(&data_ov031_0224e200, s32 *, 0) = 0;
    return 0;
}
