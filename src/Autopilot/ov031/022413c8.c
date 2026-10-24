#include <m2c.h>

M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
s32 func_ov031_02207434(M2C_UNK);

void ov38_0222316C(s32 arg0, M2C_UNK arg1) {
    if (func_ov031_02207434(arg1) != -0x1A) {
        return;
    }
    do {
        _Z19SleepCurrentContextj(0x1F4);
    } while (func_ov031_02207434(arg1) == -0x1A);
}
