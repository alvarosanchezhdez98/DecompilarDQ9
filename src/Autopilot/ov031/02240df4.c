#include <m2c.h>

M2C_UNK ov38_02222B98(void *);
extern M2C_UNK (*data_ov031_02290fc8)(s32);

void ov38_02222B1C(void *arg0) {
    data_ov031_02290fc8(M2C_FIELD(arg0, s32 *, 0x30));
    ov38_02222B98(arg0);
}
