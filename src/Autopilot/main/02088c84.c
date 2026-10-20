#include <m2c.h>

M2C_UNK func_02088c38();

void func_02088c74(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x6D) = 5;
    M2C_FIELD(arg0, s8 *, 0x90) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) | 4);
    func_02088c38();
}
