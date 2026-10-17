#include <m2c.h>

M2C_UNK func_ov003_021600b8();

void func_ov017_021b6b44(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x24) == 0) {
        return;
    }
    func_ov003_021600b8();
}
