#include <m2c.h>

s32 func_ov031_02211f24();
M2C_UNK ov00_021EC4A4();
M2C_UNK ov00_021FAB04(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern M2C_UNK data_ov031_0224e5b4;

void ov00_021EC558(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    ov00_021EC4A4();
    if (M2C_FIELD(&data_ov031_0224e5b4, void **, 4) != NULL) {
        M2C_FIELD(M2C_FIELD(&data_ov031_0224e5b4, void **, 4), s8 *, 0xC) = 1;
    }
    if (func_ov031_02211f24() != 2) {
        return;
    }
    ov00_021FAB04(arg0, arg1, arg2, arg3, arg4);
}
