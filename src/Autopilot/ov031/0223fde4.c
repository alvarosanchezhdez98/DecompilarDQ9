#include <m2c.h>

M2C_UNK func_ov031_0224030c();
M2C_UNK ov38_022220D8();
M2C_UNK ov38_02222D18();
extern M2C_UNK data_ov031_02290fbc;

void ov38_02221B0C(M2C_UNK (*arg0)()) {
    ov38_02222D18();
    ov38_022220D8();
    M2C_FIELD(&data_ov031_02290fbc, M2C_UNK (**)(s32), 0xC)(M2C_FIELD(&data_ov031_02290fbc, s32 *, 0x18));
    func_ov031_0224030c();
    M2C_FIELD(&data_ov031_02290fbc, s32 *, 0) = 0;
    arg0();
}
