#include <m2c.h>

M2C_UNK func_0207fd88(s32);
M2C_UNK func_020e2834();

void func_ov003_02174890(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x103E) == 0) {
        return;
    }
    func_0207fd88(M2C_FIELD(arg0, s32 *, 0x89C));
    if (M2C_FIELD(arg0, s32 *, 0) == 0) {
        return;
    }
    func_020e2834();
}
