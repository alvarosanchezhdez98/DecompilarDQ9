#include <m2c.h>

s32 func_0202bcbc();
s32 func_0202bcf8(void *, M2C_UNK);
M2C_UNK func_0202c288(void *);
M2C_UNK func_0202c69c(void *, M2C_UNK);

void func_0202c21c(void *arg0, M2C_UNK arg1) {
    s32 var_r4;

    var_r4 = func_0202bcbc();
    if (var_r4 < 0) {
        var_r4 = func_0202bcf8(arg0, arg1);
        if (var_r4 < 0) {
            return;
        }
    }
    M2C_FIELD(arg0, u8 *, 0x100C) = (u8) (M2C_FIELD(arg0, u8 *, 0x100C) & ~(1 << var_r4));
    func_0202c69c(arg0, arg1);
    func_0202c288(arg0);
    M2C_FIELD((arg0 + var_r4), s8 *, 0x1038) = 0;
}
