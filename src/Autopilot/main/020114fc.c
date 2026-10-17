#include <m2c.h>

M2C_UNK memcpy(M2C_UNK, void *, u8);

u8 func_020114ec(void *arg0, M2C_UNK arg1) {
    memcpy(arg1, arg0 + 0x571D, M2C_FIELD(arg0, u8 *, 0x5721));
    return M2C_FIELD(arg0, u8 *, 0x5721);
}
