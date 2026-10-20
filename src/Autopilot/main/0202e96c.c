#include <m2c.h>

M2C_UNK func_0202e98c();

void func_0202e95c(void *arg0, s16 arg1, s16 arg2) {
    if (arg2 != 0) {
        M2C_FIELD(arg0, s16 *, 0x214) = arg1;
        M2C_FIELD(arg0, s16 *, 0x216) = arg2;
        return;
    }
    func_0202e98c();
    M2C_FIELD(arg0, s16 *, 0x212) = arg1;
}
