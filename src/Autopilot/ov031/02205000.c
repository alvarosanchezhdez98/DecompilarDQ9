#include <m2c.h>

extern M2C_UNK data_ov031_0224e1c0;

void SOCLi_DhcpTimeout(void) {
    M2C_FIELD(&data_ov031_0224e1c0, s32 *, 8) = (s32) (M2C_FIELD(&data_ov031_0224e1c0, s32 *, 8) | 2);
}
