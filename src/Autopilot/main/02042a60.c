#include <m2c.h>

s32 func_020429bc();
s32 func_020429e4(s32, s32);
s32 func_02094a00();
s32 func_02094b44(s32, M2C_UNK);

s32 func_02042a50(M2C_UNK arg0, s32 arg1) {
    s32 temp_r0;

    if (arg1 == 0) {
        return 0;
    }
    temp_r0 = func_020429e4(func_020429bc(), arg1);
    if (temp_r0 != 0) {
        return temp_r0;
    }
    return func_020429e4(func_02094b44(func_02094a00(), arg0), arg1);
}
