#include <m2c.h>

M2C_UNK func_02088d4c();

void func_02088ccc(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x6B) = 5;
    M2C_FIELD(arg0, s8 *, 0x8E) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) | 8);
    func_02088d4c();
}
