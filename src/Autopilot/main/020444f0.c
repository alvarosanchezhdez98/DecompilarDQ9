#include <m2c.h>

M2C_UNK func_02066cf0(void *, M2C_UNK);
s32 func_020e1f1c(s32);
M2C_UNK func_020e23f4(s32);
M2C_UNK func_020e2478(s32);

void func_020444e0(void *arg0) {
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x38);
    if (temp_r1 != 0) {
        if (func_020e1f1c(temp_r1) == 0) {
            return;
        }
        func_02066cf0(arg0, 0);
        func_020e23f4(M2C_FIELD(arg0, s32 *, 0x38));
        func_020e2478(M2C_FIELD(arg0, s32 *, 0x38));
        return;
    }
    func_02066cf0(arg0, 0);
}
