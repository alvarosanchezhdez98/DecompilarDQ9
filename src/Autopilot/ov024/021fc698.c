#include <m2c.h>

M2C_UNK func_ov024_021fd954(void *, M2C_UNK);
s32 func_ov024_021fe698(void *, M2C_UNK);

void func_ov024_021fc698(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x71) == 0) {
        return;
    }
    if (func_ov024_021fe698(arg0, 0xC) == 0) {
        return;
    }
    func_ov024_021fd954(arg0, 0xB);
}
