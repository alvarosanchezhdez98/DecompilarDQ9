#include <m2c.h>
#pragma optimize_for_size off

extern M2C_UNK data_02111304;

void CPS_SocDatagramMode(void) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(M2C_FIELD(&data_02111304, void **, 4), void **, 0xA4);
    if (temp_r1 == NULL) {
        return;
    }
    M2C_FIELD(temp_r1, s8 *, 8) = 0xA;
    M2C_FIELD(temp_r1, s32 *, 0x44) = 0;
}
