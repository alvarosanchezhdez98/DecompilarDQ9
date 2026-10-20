#include <m2c.h>

M2C_UNK func_02012fe4();
M2C_UNK func_02033b88(void *, M2C_UNK);

s32 func_02076d34(void *arg0) {
    func_02012fe4();
    M2C_FIELD(arg0, s16 *, 0xB2) = 0;
    func_02033b88(arg0, 5);
    return 1;
}
