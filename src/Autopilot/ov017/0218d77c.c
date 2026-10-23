#include <m2c.h>

M2C_UNK func_020469b4(s32, void *);
M2C_UNK func_ov003_0217ef24(void *);

void func_ov017_0218d77c(void *arg0, s32 arg1) {
    func_ov003_0217ef24(M2C_FIELD(arg0, void **, 0x3B40));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x3B40), s32 *, 8) = arg1;
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x36FC), M2C_FIELD(arg0, void **, 0x3B40));
}
