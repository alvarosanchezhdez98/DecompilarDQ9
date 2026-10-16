#include <m2c.h>

s32 func_ov024_021da9b0(s32);
M2C_UNK func_ov024_021fd160(void *, M2C_UNK);

void func_ov024_021fd428(void *arg0) {
    if (func_ov024_021da9b0(M2C_FIELD(arg0, s32 *, 0x668)) == 0) {
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x661) != 0) {
        return;
    }
    func_ov024_021fd160(arg0, 3);
}
