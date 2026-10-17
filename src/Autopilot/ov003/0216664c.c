#include <m2c.h>

M2C_UNK func_ov003_021666c4();

void func_ov003_0216664c(void *arg0) {
    s32 temp_r1;
    s32 var_r2;
    s8 temp_r1_2;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x45C);
    var_r2 = 0;
    if (temp_r1 & 0x10) {
        var_r2 = 1;
        M2C_FIELD(arg0, s8 *, 0x4A0) = (s8) (M2C_FIELD(arg0, s8 *, 0x4A0) + 1);
    } else if (temp_r1 & 0x20) {
        var_r2 = 1;
        M2C_FIELD(arg0, s8 *, 0x4A0) = (s8) (M2C_FIELD(arg0, s8 *, 0x4A0) - 1);
    }
    temp_r1_2 = M2C_FIELD(arg0, s8 *, 0x4A0);
    if ((s32) temp_r1_2 >= 2) {
        M2C_FIELD(arg0, s8 *, 0x4A0) = 0;
    } else if ((s32) temp_r1_2 < 0) {
        M2C_FIELD(arg0, s8 *, 0x4A0) = 1;
    }
    if (var_r2 == 0) {
        return;
    }
    func_ov003_021666c4();
}
