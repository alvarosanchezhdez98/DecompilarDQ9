#include <m2c.h>
#pragma optimize_for_size off

s32 SOCL_GetHostID();
extern M2C_UNK data_ov031_0224c9e0;

s32 SOCL_SetResolver(s32 arg0, s32 arg1) {
    if (SOCL_GetHostID() == 0) {
        return -0x27;
    }
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 0) = arg0;
    M2C_FIELD(&data_ov031_0224c9e0, s32 *, 4) = arg1;
    return 0;
}
