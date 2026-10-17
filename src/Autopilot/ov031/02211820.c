#include <m2c.h>

M2C_UNK ov00_021EC210();
extern M2C_UNK data_ov031_0224e598;

void func_ov031_02211820(void) {
    ov00_021EC210();
    if (M2C_FIELD(&data_ov031_0224e598, s32 *, 0) != 9) {
        M2C_FIELD(&data_ov031_0224e598, s32 *, 0) = 0;
        M2C_FIELD(&data_ov031_0224e598, s32 *, 4) = 0;
    }
}
