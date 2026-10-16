#include <m2c.h>

M2C_UNK func_020d7534();
M2C_UNK func_020d7638(s32);

void func_ov000_02160c60(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xEA4) == 0) {
        return;
    }
    func_020d7534();
    func_020d7638(M2C_FIELD(arg0, s32 *, 0xEA4));
}
