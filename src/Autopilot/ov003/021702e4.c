#include <m2c.h>

M2C_UNK func_ov003_0216dee4(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32, s32);

void func_ov003_021702e4(void *arg0) {
    M2C_UNK var_r1;
    s32 var_r3;
    s8 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s8 *, 1);
    if ((temp_r1 != 0) && (temp_r1 != 1)) {
        var_r3 = 4;
        var_r1 = 7;
        if (M2C_FIELD(arg0, s16 *, 0xC) == 5) {
            var_r3 = 3;
            var_r1 = 6;
        }
        func_ov003_0216dee4(arg0 + 0x68, var_r1, 0xCC, 0xB, -1, var_r3, 3);
    }
}
