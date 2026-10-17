#include <m2c.h>

M2C_UNK _Z17CallMenuObjectVf0P10MenuScriptti(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK _ZN16MenuObjectClass59TurnRightEv(s32, M2C_UNK);
s32 func_ov004_0215e47c(M2C_UNK, M2C_UNK);

s32 func_ov004_02162b04(M2C_UNK arg0) {
    s32 temp_r0;

    temp_r0 = func_ov004_0215e47c(arg0, 0x82);
    if (temp_r0 != 0) {
        _ZN16MenuObjectClass59TurnRightEv(temp_r0, arg0);
        _Z17CallMenuObjectVf0P10MenuScriptti(arg0, 0x87, 1);
    }
    return 0;
}
