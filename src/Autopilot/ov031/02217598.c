#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(void *);
M2C_UNK _Z9LockMutexP5Mutex(s32);
extern M2C_UNK data_ov031_0224e5e8;

void ov00_021E8940(s32 arg0) {
    _Z9LockMutexP5Mutex(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x13D8);
    M2C_FIELD(M2C_FIELD(&data_ov031_0224e5e8, void **, 8), s32 *, 0x1004) = arg0;
    _Z11UnlockMutexP5Mutex(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x13D8);
}
