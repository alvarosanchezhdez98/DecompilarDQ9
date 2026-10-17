#include <m2c.h>
#pragma optimization_level 4

void *func_02012fe4();
M2C_UNK func_0203b4e8(s32, M2C_UNK);
s32 func_ov017_0218b5b0();

s32 func_ov017_021b2ad8(void *arg0) {
    if (M2C_FIELD(func_02012fe4(), s32 *, 0x424) != 0) {
        return M2C_FIELD(arg0, s32 *, 8);
    }
    func_0203b4e8(func_ov017_0218b5b0(), 2);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) & ~1);
    return 3;
}
