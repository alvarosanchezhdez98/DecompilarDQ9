#include <m2c.h>

M2C_UNK SOCLi_FreeCommandPacket(void *);
M2C_UNK _Z20AddContextSwitchLockv();
s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei(s32);
M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(s32);
M2C_UNK _Z23RemoveContextSwitchLockv();
M2C_UNK _Z26SwitchContextUninterruptedv();
M2C_UNK func_020c7e0c(s32, M2C_UNK, M2C_UNK);
s32 func_020c7ea0(s32, void **, M2C_UNK);

void SOCLi_FreeCommandPipe(s32 arg0) {
    void *sp0;
    s32 temp_r0;
    s32 temp_r8;

    if (arg0 == 0) {
        return;
    }
    _Z22AwaitContextCompletionP16ProcessorContext(arg0 + 0x20);
    temp_r8 = _Z20DisableIRQInterruptsv();
    _Z20AddContextSwitchLockv();
    if (func_020c7ea0(arg0, &sp0, 0) != 0) {
        do {
            if (sp0 != NULL) {
                temp_r0 = M2C_FIELD(sp0, s32 *, 8);
                if (temp_r0 != 0) {
                    func_020c7e0c(temp_r0, -0xB, 0);
                }
                SOCLi_FreeCommandPacket(sp0);
            }
        } while (func_020c7ea0(arg0, &sp0, 0) != 0);
    }
    _Z23RemoveContextSwitchLockv();
    _Z26SwitchContextUninterruptedv();
    _Z20SetIRQInterruptStatei(temp_r8);
}
