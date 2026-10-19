#include <m2c.h>

s32 func_ov001_02164624(s32, s32);
extern s32 data_ov001_02165884[0xD];

s32 func_ov001_0215a094(void *arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_r1 != NULL) {
        if ((M2C_FIELD(temp_r1, s32 *, 0x3C) == 0) && (M2C_FIELD(temp_r1, s32 *, 0) == 0xC)) {
            if ((*data_ov001_02165884 != 0) && (func_ov001_02164624(*data_ov001_02165884, M2C_FIELD(arg0, s32 *, 0x70)) != 0)) {
                M2C_FIELD(arg0, s32 *, 0x1C) = 0;
                M2C_FIELD(arg0, void **, 0x18) = NULL;
            }
        }
    }
    if ((M2C_FIELD(arg0, s32 *, 8) == 0) && (M2C_FIELD(arg0, s32 *, 0x10) == 0) && (M2C_FIELD(arg0, void **, 0x18) == NULL) && (M2C_FIELD(arg0, s32 *, 0x20) == 0) && (M2C_FIELD(arg0, s32 *, 0x28) == 0) && (M2C_FIELD(arg0, s32 *, 0x30) == 0) && (M2C_FIELD(arg0, s32 *, 0x38) == 0) && (M2C_FIELD(arg0, s32 *, 0x40) == 0)) {
        return 1;
    }
    return 0;
}
