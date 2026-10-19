#include <m2c.h>

M2C_UNK WaitByLoop(M2C_UNK);
M2C_UNK _Z24SetArm9IPCCommandHandleriPFvjjjE(M2C_UNK, M2C_UNK *);
s32 _Z29IsIPCCommandHandlerRegisteredi7IPCSide(M2C_UNK, M2C_UNK);
s32 func_ov031_0221b284(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK Callback_NVRAM;

s32 func_ov031_0221b848(void) {
    do {

    } while (_Z29IsIPCCommandHandlerRegisteredi7IPCSide(4, 1) == 0);
    _Z24SetArm9IPCCommandHandleriPFvjjjE(4, &Callback_NVRAM);
loop_3:
    if (func_ov031_0221b284(7, 0, 0, 0) != 1) {
        WaitByLoop(0x40000);
        goto loop_3;
    }
    return 1;
}
