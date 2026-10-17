#include <m2c.h>

s32 func_ov031_0221b6f0(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_0224e6a0;

s32 DWCi_BM_GetApInfo(M2C_UNK arg0) {
    if (func_ov031_0221b6f0(M2C_FIELD(&data_ov031_0224e6a0, s32 *, 8), 0x300, arg0) != 0) {
        return 1;
    }
    return 0;
}
