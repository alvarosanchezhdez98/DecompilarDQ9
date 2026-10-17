#include <m2c.h>

M2C_UNK memcpy(M2C_UNK, void *, u8);

u8 func_02011494(void *arg0, M2C_UNK arg1) {
    memcpy(arg1, arg0 + 0x5718, M2C_FIELD(arg0, u8 *, 0x571C));
    return M2C_FIELD(arg0, u8 *, 0x571C);
}
