#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(M2C_UNK *);
M2C_UNK _Z9LockMutexP5Mutex(M2C_UNK *);
extern s32 data_ov031_02290f88;
extern M2C_UNK data_ov031_02290f8c;

void ov38_022217D0(void) {
    _Z9LockMutexP5Mutex(&data_ov031_02290f8c);
    data_ov031_02290f88 = 0;
    _Z11UnlockMutexP5Mutex(&data_ov031_02290f8c);
}
