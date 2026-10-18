#include <m2c.h>

M2C_UNK _Z19ZeroInitializeMutexP5Mutex(M2C_UNK *);
extern M2C_UNK data_ov031_0224e540;
extern M2C_UNK data_ov031_0224e54c;

void WCMi_InitCpsif(void) {
    if (M2C_FIELD(&data_ov031_0224e540, u8 *, 0) != 0) {
        return;
    }
    M2C_FIELD(&data_ov031_0224e540, u8 *, 0) = 1U;
    M2C_FIELD(&data_ov031_0224e540, s32 *, 0x24) = 0;
    M2C_FIELD(&data_ov031_0224e540, s32 *, 8) = 0;
    M2C_FIELD(&data_ov031_0224e540, s32 *, 4) = 0;
    _Z19ZeroInitializeMutexP5Mutex(&data_ov031_0224e54c);
}
