#include <m2c.h>

M2C_UNK func_0205e16c();
M2C_UNK func_0205e22c();

void *func_0202c7bc(void *arg0) {
    void *var_r2;

    var_r2 = arg0;
    do {
        M2C_FIELD(var_r2, s16 *, 0x14) = 0;
        M2C_FIELD(var_r2, s16 *, 0x16) = 0;
        M2C_FIELD(var_r2, s32 *, 0x18) = 0;
        var_r2 += 0x1C;
    } while ((u32) var_r2 < (u32) (arg0 + 0x1500));
    func_0205e16c();
    func_0205e16c(arg0 + 0x150C);
    func_0205e16c(arg0 + 0x1518);
    func_0205e22c(arg0);
    return arg0;
}
