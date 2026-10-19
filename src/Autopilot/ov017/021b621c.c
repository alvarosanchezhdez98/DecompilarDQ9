#include <m2c.h>

M2C_UNK func_0204693c(void *);
M2C_UNK func_02046c98(void *);
M2C_UNK func_02046e70(void *, s32, M2C_UNK);
M2C_UNK func_ov017_0218b5b0();

void func_ov017_021b621c(void *arg0, s32 arg1, M2C_UNK arg2) {
    func_ov017_0218b5b0();
    func_0204693c(arg0);
    M2C_FIELD(arg0, s8 *, 0) = 0x16;
    func_02046e70(arg0 + 0xC, arg1, arg2);
    func_02046c98(arg0 + 0xC);
    M2C_FIELD(arg0, s8 *, 0xFC) = 0;
    M2C_FIELD(arg0, s16 *, 0xFE) = -1;
    if (arg1 == 0) {
        M2C_FIELD(arg0, s8 *, 0xFD) = 0xF;
    } else {
        M2C_FIELD(arg0, s8 *, 0xFD) = 0;
    }
    M2C_FIELD(arg0, s8 *, 8) = 1;
    M2C_FIELD(arg0, s16 *, 0x100) = -1;
}
