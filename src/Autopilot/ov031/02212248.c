#include <m2c.h>

extern M2C_UNK data_ov031_0224e5b4;

s32 ov00_021EC9A8(void) {
    if ((M2C_FIELD(&data_ov031_0224e5b4, void **, 4) != NULL) && (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5b4, void **, 4), u16 *, 4) == 6)) {
        return 1;
    }
    return 0;
}
