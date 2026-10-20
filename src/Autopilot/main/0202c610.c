#include <m2c.h>

s32 func_0202bcbc();
s32 func_0202bcf8(void *, M2C_UNK);

void func_0202c600(void *arg0, M2C_UNK arg1) {
    s32 var_r0;

    var_r0 = func_0202bcbc();
    if (var_r0 < 0) {
        var_r0 = func_0202bcf8(arg0, arg1);
        if (var_r0 < 0) {
            return;
        }
    }
    M2C_FIELD(arg0, u8 *, 0x100E) = (u8) (M2C_FIELD(arg0, u8 *, 0x100E) & ~(1 << var_r0));
}
