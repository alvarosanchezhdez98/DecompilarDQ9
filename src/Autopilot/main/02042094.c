#include <m2c.h>

s32 func_020420e8();
s32 func_020d2ff0();
M2C_UNK sprintf();
extern M2C_UNK data_020efe91;

void func_02042084(s32 arg0, M2C_UNK *arg1, s32 arg2, M2C_UNK arg3) {
    s32 temp_r4;

    temp_r4 = func_020420e8(arg1, arg3);
    sprintf(arg0 + func_020d2ff0(arg0), &data_020efe91, ((s32) (arg2 - temp_r4) >> 1) + 1);
    sprintf(arg0 + func_020d2ff0(arg0), arg1);
    func_020d2ff0(arg0);
}
