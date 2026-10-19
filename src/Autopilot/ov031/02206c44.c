#include <m2c.h>

M2C_UNK CPS_Cleanup();
M2C_UNK CPS_SetScavengerCallback(M2C_UNK);
s32 SOCL_CalmDown();
s32 SOCLi_CleanupCommandPacketQueue();
M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
extern void *data_ov031_022496a4;
extern s32 data_ov031_0224c9d0;
extern s32 data_ov031_0224e1c4;
extern M2C_UNK data_ov031_0224e1d0;

s32 SOCL_Cleanup(void) {
    s32 temp_r0;

    if (data_ov031_0224e1c4 == 0) {
        data_ov031_0224e1c4 = data_ov031_0224c9d0;
    }
    if (SOCL_CalmDown() == -0x1A) {
        do {
            _Z19SleepCurrentContextj(0x64);
        } while (SOCL_CalmDown() == -0x1A);
    }
    temp_r0 = SOCLi_CleanupCommandPacketQueue();
    if (temp_r0 >= 0) {
        CPS_Cleanup();
        CPS_SetScavengerCallback(0);
        if (M2C_FIELD(data_ov031_022496a4, s32 *, 0x28) == 0) {
            M2C_FIELD(data_ov031_022496a4, M2C_UNK (**)(s32), 0x1C)(M2C_FIELD(&data_ov031_0224e1d0, s32 *, 0x1C));
        }
        data_ov031_022496a4 = NULL;
    }
    return temp_r0;
}
