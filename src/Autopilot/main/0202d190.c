#include <m2c.h>

s32 func_020d68dc(M2C_UNK (*)(), s32, M2C_UNK *);
M2C_UNK func_0202c848();
M2C_UNK func_0202d1e4();
extern M2C_UNK data_021015a0;
extern M2C_UNK data_02101600;
extern M2C_UNK data_021016e0;

s32 func_0202d180(void) {
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 3;
    if (func_020d68dc(func_0202d1e4, M2C_FIELD(&data_021015a0, s32 (**)(M2C_UNK *, M2C_UNK *), 0x30)(&data_02101600, &data_021016e0), &data_02101600) == 2) {
        return 1;
    }
    func_0202c848();
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 9;
    return 0;
}
