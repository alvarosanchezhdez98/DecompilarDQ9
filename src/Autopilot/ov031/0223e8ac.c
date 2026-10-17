#include <m2c.h>

M2C_UNK ov38_02221AC4(M2C_UNK *);
extern M2C_UNK data_ov031_02290da0;
extern M2C_UNK ov38_022205DC;

void ov38_02220620(s32 arg0) {
    M2C_FIELD(&data_ov031_02290da0, s32 *, 0x14) = 0;
    M2C_FIELD(&data_ov031_02290da0, s32 *, 0) = arg0;
    ov38_02221AC4(&ov38_022205DC);
}
