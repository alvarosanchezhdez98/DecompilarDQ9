#include <m2c.h>

M2C_UNK _Z19SleepCurrentContextj();
M2C_UNK _Z28CycleCurrentPriorityContextsv();

void func_020d9834(s32 arg0) {
    if (arg0 != 0) {
        _Z19SleepCurrentContextj();
        return;
    }
    _Z28CycleCurrentPriorityContextsv();
}
