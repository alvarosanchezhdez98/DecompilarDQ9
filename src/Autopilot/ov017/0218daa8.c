#include <m2c.h>
#pragma optimization_level 4

M2C_UNK Vector3fix_Subtract(s32, s32, M2C_UNK *);
M2C_UNK _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv();
s32 func_ov017_0218db14(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32);

s32 func_ov017_0218daa8(M2C_UNK arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3, u8 arg4) {
    M2C_UNK sp4[3];
    s32 temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = _ZN9GameState20GetUnknownGameObjectEv();
    if (arg1 == 0) {
        return 0;
    }
    if (temp_r0 == 0) {
        return 0;
    }
    Vector3fix_Subtract(temp_r0 + 0x44, arg1, sp4);
    return func_ov017_0218db14(arg0, sp4, arg2, arg3, (s32) arg4);
}
