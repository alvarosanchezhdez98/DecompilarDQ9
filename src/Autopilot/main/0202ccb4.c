#include <m2c.h>

s32 func_020d5aec(M2C_UNK (*)());
M2C_UNK func_0202c848();
M2C_UNK func_0202ccdc();
extern M2C_UNK data_021015a0;

s32 func_0202cca4(void) {
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 3;
    if (func_020d5aec(func_0202ccdc) == 2) {
        return 1;
    }
    func_0202c848();
    return 0;
}
