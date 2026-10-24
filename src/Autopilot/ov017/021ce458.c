#include <m2c.h>
#pragma optimization_level 4

u16 *func_02012fe4();
M2C_UNK func_ov017_021913d0(M2C_UNK, u16);
M2C_UNK func_ov017_02191484(M2C_UNK);

void func_ov017_021ce458(s32 arg0, void *arg1, s32 arg2, M2C_UNK arg3) {
    if (M2C_FIELD(arg1, u16 *, 6) == *func_02012fe4()) {
        func_ov017_021913d0(arg3, M2C_FIELD(arg1, u16 *, 4));
        return;
    }
    func_ov017_02191484(arg3);
}
