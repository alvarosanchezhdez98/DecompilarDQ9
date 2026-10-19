#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(s32);
M2C_UNK _Z9LockMutexP5Mutex(s32);
extern M2C_UNK data_ov031_0224e5e8;

s32 ov00_021E7E5C(void) {
    s32 temp_r4;

    if (M2C_FIELD(&data_ov031_0224e5e8, void **, 8) == NULL) {
        return 0x16;
    }
    _Z9LockMutexP5Mutex(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x13D8);
    temp_r4 = M2C_FIELD(M2C_FIELD(&data_ov031_0224e5e8, void **, 8), s32 *, 0x1004);
    _Z11UnlockMutexP5Mutex(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x13D8);
    return temp_r4;
}
