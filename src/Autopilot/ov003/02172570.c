#include <m2c.h>

void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021b2074(s32, M2C_UNK);

s32 func_ov003_02172570(u8 *arg0, M2C_UNK arg1) {
    if (*arg0 != 9) {
        return 0;
    }
    func_ov017_021b2074(M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x3B48), arg1);
    return 1;
}
