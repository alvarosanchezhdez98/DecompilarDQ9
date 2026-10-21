#include <m2c.h>

s32 func_020d5214(M2C_UNK (*)());
M2C_UNK func_0202c848();
M2C_UNK func_0202cd28();
M2C_UNK func_0202dd28();

void func_0202ccdc(void *arg0) {
    s32 var_r0;

    if (M2C_FIELD(arg0, u16 *, 2) != 0) {
        func_0202c848();
        func_0202dd28();
        return;
    }
    if (func_020d5214(func_0202cd28) == 2) {
        var_r0 = 1;
    } else {
        func_0202c848();
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        return;
    }
    func_0202dd28();
}
