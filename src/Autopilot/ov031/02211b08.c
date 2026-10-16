#include <m2c.h>

extern M2C_UNK data_ov031_0224e5a4;

void ov00_021EC24C(s32 arg0, s32 arg1) {
    if (M2C_FIELD(&data_ov031_0224e5a4, s32 *, 0) != 9) {
        M2C_FIELD(&data_ov031_0224e5a4, s32 *, 0) = arg0;
        M2C_FIELD(&data_ov031_0224e5a4, s32 *, 4) = arg1;
    }
}
