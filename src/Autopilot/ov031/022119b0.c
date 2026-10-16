#include <m2c.h>

extern M2C_UNK data_ov031_0224e5a4;

s32 ov00_021EC0FC(s32 *arg0) {
    if (arg0 != NULL) {
        *arg0 = M2C_FIELD(&data_ov031_0224e5a4, s32 *, 4);
    }
    return M2C_FIELD(&data_ov031_0224e5a4, s32 *, 0);
}
