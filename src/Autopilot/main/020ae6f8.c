#include <m2c.h>

u16 *func_02012fe4();
M2C_UNK func_020ae4ec(M2C_UNK, M2C_UNK);
M2C_UNK func_020ae694(s32, M2C_UNK, M2C_UNK);

void func_020ae6e8(s32 arg0) {
    M2C_UNK var_r1;

    if (*func_02012fe4() != 0x2010) {
        return;
    }
    func_020ae694(arg0, 0, 2);
    if (arg0 == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_020ae4ec(0, var_r1);
}
