#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_ov001_021537a0(M2C_UNK *);
extern M2C_UNK data_ov001_021658b8;
extern M2C_UNK data_ov001_021658d8;

s32 func_ov001_0215e27c(void) {
    func_ov001_021537a0(&data_ov001_021658d8);
    M2C_FIELD(&data_ov001_021658b8, s8 *, 0x8C) = 0;
    return 1;
}
