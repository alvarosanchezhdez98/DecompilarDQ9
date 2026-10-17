#include <m2c.h>

extern M2C_UNK data_02111304;

void CPS_SetRootCa(s32 arg0, s32 arg1) {
    void *temp_r2;
    void *temp_r2_2;

    temp_r2 = M2C_FIELD(M2C_FIELD(&data_02111304, void **, 4), void **, 0xA4);
    if (temp_r2 != NULL) {
        temp_r2_2 = M2C_FIELD(temp_r2, void **, 0xC);
        if (temp_r2_2 != NULL) {
            M2C_FIELD(temp_r2_2, s32 *, 0x814) = arg0;
            M2C_FIELD(temp_r2_2, s32 *, 0x818) = arg1;
        }
    }
}
