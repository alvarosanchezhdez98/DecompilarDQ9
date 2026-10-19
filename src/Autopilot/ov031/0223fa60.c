#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(M2C_UNK *);
M2C_UNK _Z9LockMutexP5Mutex(M2C_UNK *);
extern s32 data_ov031_02290f88;
extern M2C_UNK data_ov031_02290f8c;

s32 ov38_02221788(void) {
    s32 var_r4;

    _Z9LockMutexP5Mutex(&data_ov031_02290f8c);
    if (data_ov031_02290f88 == 0) {
        var_r4 = 1;
    } else {
        var_r4 = 0;
    }
    if (var_r4 != 0) {
        data_ov031_02290f88 = 1;
    }
    _Z11UnlockMutexP5Mutex(&data_ov031_02290f8c);
    return var_r4;
}
