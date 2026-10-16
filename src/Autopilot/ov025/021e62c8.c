#include <m2c.h>

M2C_UNK func_ov000_02160130();
s32 func_ov000_02162954();
s32 func_ov025_021ed0fc(s32);
extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e62c8(void) {
    if (func_ov025_021ed0fc(M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC) + 0x22C) == 0) {
        return 0;
    }
    func_ov000_02160130();
    if (func_ov000_02162954() == 0) {
        return 1;
    }
    return 0;
}
