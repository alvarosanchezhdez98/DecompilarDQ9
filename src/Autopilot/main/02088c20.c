#include <m2c.h>

M2C_UNK func_02088c9c();

void func_02088c10(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x6C) = 5;
    M2C_FIELD(arg0, s8 *, 0x8F) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) | 2);
    func_02088c9c();
}
