#include <m2c.h>

s32 _Z16GetProcessorModev();
M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
extern s32 data_ov031_0224c9d0;
extern s32 data_ov031_0224e1c4;
extern s32 data_ov031_0224e1c8;

s32 SOCL_GetHostID(void) {
    if (data_ov031_0224c9d0 == 0) {
        if (((data_ov031_0224e1c8 & 3) == 1) && (_Z16GetProcessorModev() != 0x12)) {
            _Z19SleepCurrentContextj(0xA);
        }
    } else if (data_ov031_0224e1c4 == 0) {
        data_ov031_0224e1c4 = data_ov031_0224c9d0;
    }
    return data_ov031_0224c9d0;
}
