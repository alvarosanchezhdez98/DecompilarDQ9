#include <m2c.h>

s32 func_020421a0();
M2C_UNK func_0204359c(s32, M2C_UNK);
M2C_UNK func_020439b0(s32, M2C_UNK);
M2C_UNK func_0207fd88();

void func_ov017_021aaec8(void *arg0) {
    s32 temp_r0;

    if ((M2C_FIELD(arg0, s32 *, 0x14) == 5) && (M2C_FIELD(arg0, s32 *, 0x18) != 0)) {
        func_0207fd88();
    }
    temp_r0 = func_020421a0();
    func_0204359c(temp_r0, 8);
    func_020439b0(temp_r0, 0);
}
