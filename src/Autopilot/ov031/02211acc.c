#include <m2c.h>

extern M2C_UNK data_ov031_0224e5a4;

void ov00_021EC210(void) {
    if (M2C_FIELD(&data_ov031_0224e5a4, s32 *, 0) != 9) {
        M2C_FIELD(&data_ov031_0224e5a4, s32 *, 0) = 0;
        M2C_FIELD(&data_ov031_0224e5a4, s32 *, 4) = 0;
    }
}
