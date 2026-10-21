#include <m2c.h>

s32 func_ov017_021d60f4(M2C_UNK);
s32 func_0209dccc();
M2C_UNK func_0209fb90(s32, s32);

s32 func_0209d710(M2C_UNK arg0) {
    s32 temp_r0;

    temp_r0 = func_0209dccc();
    if (temp_r0 == 0) {
        return 0;
    }
    func_0209fb90(temp_r0, func_ov017_021d60f4(arg0));
    return 1;
}
