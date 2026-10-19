#include <m2c.h>

M2C_UNK ov00_021EC2EC(M2C_UNK, s32, M2C_UNK);
extern M2C_UNK data_ov031_0224e5dc;

void ov00_021FE070(void) {
    if (M2C_FIELD(&data_ov031_0224e5dc, s32 *, 4) != 0) {
        ov00_021EC2EC(1, M2C_FIELD(&data_ov031_0224e5dc, s32 *, 4), 0);
        M2C_FIELD(&data_ov031_0224e5dc, s32 *, 4) = 0;
    }
    if (M2C_FIELD(&data_ov031_0224e5dc, s32 *, 0) == 0) {
        return;
    }
    ov00_021EC2EC(1, M2C_FIELD(&data_ov031_0224e5dc, s32 *, 0), 0);
    M2C_FIELD(&data_ov031_0224e5dc, s32 *, 0) = 0;
}
