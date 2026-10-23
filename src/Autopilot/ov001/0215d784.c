#include <m2c.h>

s32 func_ov017_021d60f4();
M2C_UNK func_ov001_0215905c(s32, s32);
extern M2C_UNK data_ov001_02165880;

s32 func_ov001_0215d784(void) {
    func_ov001_0215905c(M2C_FIELD(&data_ov001_02165880, s32 *, 0x24), func_ov017_021d60f4());
    return 1;
}
