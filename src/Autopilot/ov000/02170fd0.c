#include <m2c.h>

M2C_UNK func_ov000_0217636c(void *, M2C_UNK);
M2C_UNK func_ov000_0217f518();

void func_ov000_02170fd0(void *arg0, M2C_UNK arg1) {
    func_ov000_0217f518();
    if (M2C_FIELD(arg0, s32 *, 0x38) == 0) {
        return;
    }
    func_ov000_0217636c(arg0, arg1);
}
