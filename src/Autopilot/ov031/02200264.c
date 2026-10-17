#include <m2c.h>

M2C_UNK _Z19SleepCurrentContextj();
M2C_UNK _Z28CycleCurrentPriorityContextsv();
extern M2C_UNK data_ov031_0224c980;

void OS_YieldThread__(void) {
    if (M2C_FIELD(&data_ov031_0224c980, s32 *, 0x24) == 0) {
        _Z28CycleCurrentPriorityContextsv();
        return;
    }
    _Z19SleepCurrentContextj();
}
