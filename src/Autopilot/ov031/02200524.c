#include <m2c.h>

extern M2C_UNK data_ov031_0224c980;

void CPS_SetScavengerCallback(s32 arg0) {
    M2C_FIELD(&data_ov031_0224c980, s32 *, 0x3C) = arg0;
}
