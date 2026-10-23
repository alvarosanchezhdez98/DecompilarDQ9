#include <m2c.h>

void *_Z14GetMenuObject7P10MenuScriptt(M2C_UNK, M2C_UNK);
void _ZN16MenuObjectClass76SetRowEt(void *, u16);

s32 func_ov004_021694e8(M2C_UNK arg0) {
    void *temp_r0;

    temp_r0 = _Z14GetMenuObject7P10MenuScriptt(arg0, 0x65);
    if (temp_r0 != NULL) {
        _ZN16MenuObjectClass76SetRowEt(temp_r0, 1U);
    }
    return 0;
}
