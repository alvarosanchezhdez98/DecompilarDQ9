#include <m2c.h>

M2C_UNK func_ov031_02211f24();
extern M2C_UNK data_ov031_0224e5b4;

s32 ov00_021EC5B4(void) {
    s32 var_r0;

    if (M2C_FIELD(&data_ov031_0224e5b4, void **, 4) == NULL) {
        return 0;
    }
    if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5b4, void **, 4), s32 *, 0) != 0) {
        M2C_FIELD(M2C_FIELD(&data_ov031_0224e5b4, void **, 4), s16 *, 4) = 3;
        func_ov031_02211f24();
        if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5b4, void **, 4), u8 *, 0xC) != 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
