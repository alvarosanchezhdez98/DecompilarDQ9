#include <m2c.h>

extern M2C_UNK data_ov031_0224e5ac;

void ov00_021EC294(s32 arg0, s32 arg1) {
    M2C_FIELD(&data_ov031_0224e5ac, s32 *, 4) = arg0;
    M2C_FIELD(&data_ov031_0224e5ac, s32 *, 0) = arg1;
}
