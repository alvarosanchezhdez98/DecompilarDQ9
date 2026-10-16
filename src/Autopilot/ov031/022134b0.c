#include <m2c.h>

extern M2C_UNK data_ov031_0224e5c4;

u8 ov00_021FAECC(void) {
    if (M2C_FIELD(&data_ov031_0224e5c4, void **, 0xC) != NULL) {
        return M2C_FIELD(M2C_FIELD(&data_ov031_0224e5c4, void **, 0xC), u8 *, 9);
    }
    return 0U;
}
