#include <m2c.h>

s32 func_02012444(M2C_UNK *, s32);
M2C_UNK func_ov000_02175628(s32);
M2C_UNK func_ov000_021756b8(s32);
M2C_UNK func_ov000_02176e3c(s32, void *, s8, s32, s32, s32);
M2C_UNK func_ov000_0217ab8c(void *, s32, s32);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;
extern M2C_UNK data_ov000_02184294;

s32 func_ov000_0217c094(void *arg0) {
    void *temp_r3;

    func_ov000_02175628(M2C_FIELD(&data_ov000_02184294, s32 *, 8));
    if ((func_02012444(&data_02114e30, 0x802) == 0) && (M2C_FIELD(&data_02114e54, u8 *, 0x55) == 0)) {

    } else {
        func_ov000_021756b8(M2C_FIELD(&data_ov000_02184294, s32 *, 8));
        temp_r3 = arg0 + 8;
        M2C_FIELD((temp_r3 + M2C_FIELD(temp_r3, s8 *, 0x10)), s8 *, 8) = 0;
        M2C_FIELD(temp_r3, s8 *, 0x10) = (s8) (M2C_FIELD(temp_r3, s8 *, 0x10) - 1);
        func_ov000_0217ab8c(arg0, M2C_FIELD(&data_ov000_02184294, s32 *, 4), M2C_FIELD(&data_ov000_02184294, s32 *, 0));
        func_ov000_02176e3c(M2C_FIELD(&data_ov000_02184294, s32 *, 8), arg0, M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x18)), s8 *, 0x10), M2C_FIELD(&data_ov000_02184294, s32 *, 4), M2C_FIELD(&data_ov000_02184294, s32 *, 0), 0);
    }
    return -1;
}
