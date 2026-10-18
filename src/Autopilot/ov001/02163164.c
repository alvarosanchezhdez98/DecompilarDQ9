#include <m2c.h>

void *func_ov017_0218b5b0();
s32 func_ov017_021bbc04(s32);
M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);

s32 func_ov001_02163164(M2C_UNK arg0) {
    if (func_ov017_021bbc04(M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x3734)) != 0) {
        func_ov017_021d6134(arg0, 1);
    } else {
        func_ov017_021d6134(arg0, 0);
    }
    return 1;
}
