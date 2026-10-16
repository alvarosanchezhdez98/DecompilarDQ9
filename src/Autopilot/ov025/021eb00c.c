#include <m2c.h>

M2C_UNK func_ov000_02160130();
M2C_UNK func_ov000_021639b4();

void func_ov025_021eb00c(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C4) & 4) {
        return;
    }
    func_ov000_02160130();
    func_ov000_021639b4();
    M2C_FIELD(arg0, s32 *, 0x1C4) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C4) | 4);
}
