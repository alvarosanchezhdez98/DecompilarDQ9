#include <m2c.h>

M2C_UNK func_ov001_0215acb4(s32);
extern M2C_UNK data_ov001_02165880;

void func_ov001_0215acd4(s32 arg0) {
    if (M2C_FIELD(&data_ov001_02165880, s32 *, 4) == 0) {
        return;
    }
    func_ov001_0215acb4(M2C_FIELD(&data_ov001_02165880, s32 *, 4) + (arg0 * 0x10));
}
