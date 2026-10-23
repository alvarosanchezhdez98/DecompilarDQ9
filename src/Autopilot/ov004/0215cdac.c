#include <m2c.h>

void *func_ov004_02156ed0(M2C_UNK, M2C_UNK);
M2C_UNK func_ov004_02158fec(M2C_UNK);

s32 func_ov004_0215cdac(M2C_UNK arg0) {
    s16 temp_r1;
    s16 temp_r2;
    s16 var_r1;
    void *temp_r0;

    temp_r0 = func_ov004_02156ed0(arg0, 0x5B);
    temp_r2 = M2C_FIELD(temp_r0, s16 *, 0x5E);
    temp_r1 = M2C_FIELD(temp_r0, s16 *, 0x5C) + 1;
    var_r1 = temp_r1;
    if ((s32) temp_r2 <= (s32) temp_r1) {
        var_r1 = 0;
    }
    M2C_FIELD(temp_r0, s16 *, 0x5C) = var_r1;
    M2C_FIELD(temp_r0, s16 *, 0x5E) = temp_r2;
    func_ov004_02158fec(arg0);
    return 0;
}
