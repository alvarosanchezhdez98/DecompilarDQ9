#include <m2c.h>

M2C_UNK func_ov000_02160c60();

void func_ov017_021b8420(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x6AC) == 0) {
        return;
    }
    func_ov000_02160c60();
}
