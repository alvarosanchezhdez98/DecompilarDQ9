#include <m2c.h>

M2C_UNK func_ov000_02176e3c(s32, void *, s8, s32, s32, s32);
extern s32 data_ov000_02183ff0;
extern M2C_UNK data_ov000_02184288;

void func_ov000_02170078(void *arg0) {
    s8 temp_r2;

    temp_r2 = M2C_FIELD(arg0, s8 *, 0x43D);
    if ((s32) temp_r2 >= 0) {
        if (M2C_FIELD(&data_ov000_02184288, s32 *, 8) != 0) {
            func_ov000_02176e3c(M2C_FIELD(&data_ov000_02184288, s32 *, 8), arg0, temp_r2, data_ov000_02183ff0, M2C_FIELD(&data_ov000_02184288, s32 *, 4), 1);
        }
        M2C_FIELD(arg0, s8 *, 0x43D) = -1;
    }
}
