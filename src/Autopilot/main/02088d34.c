#include <m2c.h>

M2C_UNK func_02088cf4();

void func_02088d24(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x7B) = 5;
    M2C_FIELD(arg0, s8 *, 0x9E) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) | 0x10);
    func_02088cf4();
}
