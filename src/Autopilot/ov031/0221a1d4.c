#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(void *);
M2C_UNK _Z9LockMutexP5Mutex(void *);
extern void *data_ov031_0224e60c;

void ov00_021EB56C(s32 arg0) {
    _Z9LockMutexP5Mutex(data_ov031_0224e60c + 0x11DC);
    M2C_FIELD(data_ov031_0224e60c, s32 *, 0x1000) = arg0;
    _Z11UnlockMutexP5Mutex(data_ov031_0224e60c + 0x11DC);
}
