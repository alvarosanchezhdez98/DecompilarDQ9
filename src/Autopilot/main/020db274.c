#include <m2c.h>

M2C_UNK func_020d8654();
M2C_UNK func_020d8694();
M2C_UNK func_020db360(void *, M2C_UNK);
s8 func_020db9a8(void *);

void func_020db264(void *arg0, u8 arg1, s8 arg2, s8 arg3, s32 arg4) {
    M2C_UNK var_r1;

    if ((M2C_FIELD(arg0, u8 *, 0x50) != 0) && (arg1 != 0)) {
        return;
    }
    func_020d8654();
    if (arg3 == 0) {
        M2C_FIELD(arg0, s16 *, 0x66) = 0;
    }
    M2C_FIELD(arg0, u8 *, 0x50) = arg1;
    M2C_FIELD(arg0, s8 *, 0x52) = arg2;
    M2C_FIELD(arg0, s8 *, 0x53) = arg3;
    M2C_FIELD(arg0, s8 *, 0x54) = (s8) arg4;
    if (arg1 == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_020db360(arg0, var_r1);
    M2C_FIELD(arg0, s8 *, 0x3C) = func_020db9a8(arg0);
    func_020d8694();
}
