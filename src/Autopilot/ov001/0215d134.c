#include <m2c.h>

M2C_UNK func_ov001_021588e4(s32);
extern M2C_UNK data_ov001_02165880;
extern M2C_UNK data_ov001_021658b8;

s32 func_ov001_0215d134(void) {
    func_ov001_021588e4(M2C_FIELD(&data_ov001_02165880, s32 *, 0x24));
    if (M2C_FIELD(&data_ov001_021658b8, s32 *, 0xE4) == 0) {
        M2C_FIELD(&data_ov001_021658b8, s32 *, 0xE4) = 1;
    }
    return 1;
}
