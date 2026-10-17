#include <m2c.h>

M2C_UNK func_ov017_021c9954(u16, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov017_021c9cb0(M2C_UNK arg0, void *arg1) {
    M2C_UNK var_r2;

    if (M2C_FIELD(arg1, u8 *, 6) != 0) {
        var_r2 = 1;
    } else {
        var_r2 = 0;
    }
    func_ov017_021c9954(M2C_FIELD(arg1, u16 *, 4), 1, var_r2, arg0);
}
