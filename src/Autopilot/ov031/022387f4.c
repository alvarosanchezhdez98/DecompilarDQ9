#include <m2c.h>

s32 MB_StartParentFromIdle(M2C_UNK);
M2C_UNK func_020c9be0();
s32 ov13_0223CB7C(M2C_UNK);
M2C_UNK ov13_0223D448(M2C_UNK);

void ov13_0223CB34(M2C_UNK arg0, M2C_UNK arg1) {
    ov13_0223D448(2);
    if (MB_StartParentFromIdle(arg1) != 0) {
        ov13_0223D448(7);
        return;
    }
    if (ov13_0223CB7C(arg0) != 0) {
        return;
    }
    func_020c9be0();
}
