#include <m2c.h>

s32 func_02088514(s32);
M2C_UNK func_ov024_021fd160(void *, M2C_UNK);

void func_ov024_021fd3f0(void *arg0) {
    if (func_02088514(M2C_FIELD(M2C_FIELD(arg0, void **, 0x668), s32 *, 0x138)) == 0) {
        return;
    }
    if (M2C_FIELD(arg0, u8 *, 0x661) != 0) {
        return;
    }
    func_ov024_021fd160(arg0, 2);
}
