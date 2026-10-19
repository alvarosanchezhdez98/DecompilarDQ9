#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(void *);
M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(void *);
M2C_UNK _Z9LockMutexP5Mutex(void *);

void ov00_021E9210(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1000) != 0xFF) {
        return;
    }
    _Z9LockMutexP5Mutex(arg0 + 0x1BF8);
    M2C_FIELD(arg0, s32 *, 0x1C10) = 1;
    _Z11UnlockMutexP5Mutex(arg0 + 0x1BF8);
    if (M2C_FIELD(arg0, s32 *, 0x1BA4) == 0) {
        return;
    }
    _Z22AwaitContextCompletionP16ProcessorContext(arg0 + 0x1B38);
}
