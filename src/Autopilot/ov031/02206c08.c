#include <m2c.h>
#pragma optimization_level 4

M2C_UNK SOCLi_CleanupSocket();
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
extern s32 data_ov031_0224e230;

void SOCLi_TrashSocket(void) {
    s32 temp_r5;

    temp_r5 = _Z20DisableIRQInterruptsv();
    if (data_ov031_0224e230 != 0) {
        do {
            SOCLi_CleanupSocket();
        } while (data_ov031_0224e230 != 0);
    }
    _Z20SetIRQInterruptStatei(temp_r5);
}
