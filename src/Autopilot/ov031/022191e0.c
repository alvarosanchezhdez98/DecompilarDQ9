#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(void *);
M2C_UNK _Z9LockMutexP5Mutex(void *);
extern void *data_ov031_0224e60c;

s32 ov00_021EA580(void) {
    s32 temp_r4;

    _Z9LockMutexP5Mutex(data_ov031_0224e60c + 0x11DC);
    temp_r4 = M2C_FIELD(data_ov031_0224e60c, s32 *, 0x1000);
    _Z11UnlockMutexP5Mutex(data_ov031_0224e60c + 0x11DC);
    return temp_r4;
}
