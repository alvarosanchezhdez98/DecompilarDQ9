#include <m2c.h>

M2C_UNK func_ov003_0215fb94();
M2C_UNK func_ov017_021b67d8(void *);

void func_ov017_021b6b8c(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x24) != 0) {
        func_ov003_0215fb94();
    }
    func_ov017_021b67d8(arg0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
