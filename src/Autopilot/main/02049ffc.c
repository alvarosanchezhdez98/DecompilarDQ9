#include <m2c.h>

s32 _ZNK10AlphaTween9GetTargetEv(s32);

s32 func_02049fec(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x13C);
    if (temp_r0 == 0) {
        return 0;
    }
    return _ZNK10AlphaTween9GetTargetEv(temp_r0 + 0x60);
}
