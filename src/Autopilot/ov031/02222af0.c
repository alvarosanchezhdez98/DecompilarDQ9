#include <m2c.h>

M2C_UNK func_ov031_02222aa4(M2C_UNK *);
extern M2C_UNK data_ov031_0224f670;

#pragma thumb on
void func_ov031_02222af0(void) {
    M2C_UNK sp0[3];

    func_ov031_02222aa4(sp0);
    M2C_FIELD(&data_ov031_0224f670, M2C_UNK (**)(M2C_UNK *), 0x7C)(sp0);
}
#pragma thumb off
