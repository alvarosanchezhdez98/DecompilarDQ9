#include <m2c.h>

extern M2C_UNK data_02111304;

void CPS_SocUnRegister(void) {
    M2C_FIELD(M2C_FIELD(&data_02111304, void **, 4), s32 *, 0xA4) = 0;
}
