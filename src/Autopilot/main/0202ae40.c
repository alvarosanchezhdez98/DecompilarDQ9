#include <m2c.h>

extern M2C_UNK data_020fefec;

void func_0202ae30(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 4) == 0x10) {
        M2C_FIELD(&data_020fefec, s32 *, 8) = 2;
    }
}
