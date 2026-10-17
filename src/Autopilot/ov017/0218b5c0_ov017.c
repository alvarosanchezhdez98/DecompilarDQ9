#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_02020028(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov017_021d82e0;

void func_ov017_0218b5c0(M2C_UNK arg0, M2C_UNK arg1) {
    s32 temp_r0;

    if (M2C_FIELD(&data_ov017_021d82e0, void **, 4) != NULL) {
        temp_r0 = M2C_FIELD(M2C_FIELD(&data_ov017_021d82e0, void **, 4), s32 *, 0x36D0);
        if (temp_r0 != 0) {
            func_02020028(temp_r0, arg0, arg1);
        }
    }
}
