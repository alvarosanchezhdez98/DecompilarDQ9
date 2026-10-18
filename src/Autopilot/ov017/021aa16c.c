#include <m2c.h>

M2C_UNK func_0204693c(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_ov017_0218b5b0();

void func_ov017_021aa16c(void *arg0) {
    func_ov017_0218b5b0();
    func_0204693c(arg0);
    M2C_FIELD(arg0, s8 *, 0) = 0x3C;
    memset(arg0 + 8, -1, 8);
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    M2C_FIELD(arg0, s8 *, 0x11) = 0;
    M2C_FIELD(arg0, s16 *, 0x12) = 0;
}
