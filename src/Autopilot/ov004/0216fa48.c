#include <m2c.h>

M2C_UNK func_020a1e54(M2C_UNK);
M2C_UNK func_020e455c();

void func_ov004_0216fa48(void *arg0) {
    func_020e455c();
    if (M2C_FIELD(arg0, u8 *, 0xF) == 0) {
        return;
    }
    func_020a1e54(1);
    M2C_FIELD(arg0, u8 *, 0xF) = 0U;
}
