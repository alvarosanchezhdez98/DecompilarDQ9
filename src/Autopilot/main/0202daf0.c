#include <m2c.h>

M2C_UNK func_020c9be0();
extern M2C_UNK data_021015a0;

void func_0202dae0(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 2) != 8) {
        return;
    }
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
    func_020c9be0();
}
