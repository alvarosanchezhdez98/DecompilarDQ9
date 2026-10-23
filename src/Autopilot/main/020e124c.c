#include <m2c.h>

M2C_UNK func_02012528(M2C_UNK *, M2C_UNK);
M2C_UNK func_02012ba8(M2C_UNK *, M2C_UNK);
s32 func_020e11e4();
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;
extern M2C_UNK data_02153628;

void func_020e123c(void) {
    if (func_020e11e4() != 0) {
        return;
    }
    M2C_FIELD(&data_02153628, s32 *, 4) = 0;
    M2C_FIELD(&data_02153628, s32 *, 8) = 0;
    M2C_FIELD(&data_02153628, s32 *, 0) = 0;
    func_02012528(&data_02114e30, 1);
    func_02012ba8(&data_02114e54, 1);
}
