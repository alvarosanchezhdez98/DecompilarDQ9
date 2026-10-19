#include <m2c.h>

M2C_UNK func_ov031_0223fa08();
M2C_UNK func_ov031_0223fa5c();
M2C_UNK ov38_0221FF7C();
extern M2C_UNK data_ov031_02290da0;

void ov38_022205DC(void) {
    ov38_0221FF7C();
    func_ov031_0223fa08();
    func_ov031_0223fa5c();
    M2C_FIELD(&data_ov031_02290da0, M2C_UNK (**)(s32), 0x20)(M2C_FIELD(&data_ov031_02290da0, s32 *, 8));
    M2C_FIELD(&data_ov031_02290da0, M2C_UNK (**)(s32), 0x20)(M2C_FIELD(&data_ov031_02290da0, s32 *, 0x10));
    M2C_FIELD(&data_ov031_02290da0, M2C_UNK (**)(), 0)();
}
