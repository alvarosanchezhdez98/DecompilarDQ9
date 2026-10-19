#include <m2c.h>

M2C_UNK func_02088818(void *, M2C_UNK);

void func_020887b4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) | 0x80);
    func_02088818(arg0, 4);
}
