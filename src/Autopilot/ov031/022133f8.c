#include <m2c.h>

extern M2C_UNK data_ov031_0224e5c4;

s32 ov00_021FAE14(s32 arg0) {
    if (arg0 & 1) {
        return M2C_FIELD(&data_ov031_0224e5c4, s32 *, 0xC);
    }
    if (arg0 & 2) {
        return M2C_FIELD(&data_ov031_0224e5c4, s32 *, 0);
    }
    if (arg0 & 4) {
        return M2C_FIELD(&data_ov031_0224e5c4, s32 *, 4);
    }
    if (arg0 & 8) {
        return M2C_FIELD(&data_ov031_0224e5c4, s32 *, 8);
    }
    if (arg0 & 0x10) {
        return M2C_FIELD(&data_ov031_0224e5c4, s32 *, 0x10);
    }
    return 0;
}
