#include <m2c.h>

s32 SOCLi_GetSizeCommandPipe(void *);
M2C_UNK _Z15PopulateContextP16ProcessorContextjjjjj(s32, M2C_UNK *, s32, s32, s32, s32);
M2C_UNK _Z19ZeroInitializeMutexP5Mutex(s32);
M2C_UNK _Z25MarkContextReadyAndSwitchP16ProcessorContext(s32);
M2C_UNK func_020c7de4(s32, s32, u8);
extern M2C_UNK func_ov031_022052b4;

s32 SOCLi_InitCommandPipe(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_r4;

    temp_r4 = SOCLi_GetSizeCommandPipe(arg2);
    func_020c7de4(arg1, arg0, M2C_FIELD(arg2, u8 *, 3));
    _Z19ZeroInitializeMutexP5Mutex(arg1 + 0xE0);
    _Z15PopulateContextP16ProcessorContextjjjjj(arg1 + 0x20, &func_ov031_022052b4, arg1, arg0 + temp_r4, (s32) M2C_FIELD(arg2, u16 *, 0), (s32) M2C_FIELD(arg2, u8 *, 2));
    _Z25MarkContextReadyAndSwitchP16ProcessorContext(arg1 + 0x20);
    return arg0 + temp_r4;
}
