#include <m2c.h>

s32 func_0202ae18();
s32 func_0202b7d8();
s32 func_0202c508(s32);
M2C_UNK func_ov017_021ced48(M2C_UNK, M2C_UNK);

void func_020e36f0(u8 *arg0) {
    s32 temp_r4;

    temp_r4 = func_0202ae18();
    if (func_0202b7d8() == 0) {
        return;
    }
    if (func_0202c508(temp_r4) != 0) {
        func_0202ae18();
        if (func_0202b7d8() != 0) {
            *arg0 |= 1;
        }
        return;
    }
    func_ov017_021ced48(0, 0);
}
