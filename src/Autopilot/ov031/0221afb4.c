#include <m2c.h>

s32 func_ov031_0221b6f0(M2C_UNK, M2C_UNK, u16 *);
extern M2C_UNK data_ov031_0224e6a0;

s32 DWCi_BACKUPlInit(u16 *arg0) {
    if (func_ov031_0221b6f0(0x20, 0x20, arg0) == 0) {
        return 0;
    }
    M2C_FIELD(&data_ov031_0224e6a0, s32 *, 8) = (s32) ((*arg0 * 8) - 0x400);
    return 1;
}
