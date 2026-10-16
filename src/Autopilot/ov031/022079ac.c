#include <m2c.h>

M2C_UNK CPS_SetSsl();
M2C_UNK _Z11UnlockMutexP5Mutex();
M2C_UNK _Z9LockMutexP5Mutex();

s32 SOCLi_EnableSslCallBack(void *arg0) {
    s32 temp_r1;
    void *temp_r4;
    void *temp_r5;
    void *temp_r6;

    temp_r4 = M2C_FIELD(arg0, void **, 4);
    temp_r5 = M2C_FIELD(temp_r4, void **, 0x64);
    temp_r6 = M2C_FIELD(temp_r5, void **, 0xC4);
    _Z9LockMutexP5Mutex(temp_r5 + 0xE0);
    temp_r1 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_r1 != 0) {
        M2C_FIELD(temp_r6, s32 *, 0xC) = temp_r1;
        CPS_SetSsl(1);
        M2C_FIELD(temp_r4, s8 *, 0x73) = 4;
    } else {
        M2C_FIELD(temp_r4, s8 *, 0x73) = 0;
        CPS_SetSsl();
        M2C_FIELD(temp_r6, s32 *, 0xC) = 0;
    }
    _Z11UnlockMutexP5Mutex(temp_r5 + 0xE0);
    return 0;
}
