#include <m2c.h>

M2C_UNK ov00_021FAC8C(M2C_UNK, s32, s32);
extern M2C_UNK data_ov031_0224e5c4;

void ov00_021FAFD8(void) {
    ov00_021FAC8C(8, M2C_FIELD(&data_ov031_0224e5c4, s32 *, 8), 0xC);
    ov00_021FAC8C(0x10, M2C_FIELD(&data_ov031_0224e5c4, s32 *, 0x10), 0xD18);
}
