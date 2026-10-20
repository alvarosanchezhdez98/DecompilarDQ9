#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(void *);
M2C_UNK _Z22AwaitContextCompletionP16ProcessorContext(void *);
M2C_UNK _Z9LockMutexP5Mutex(s32);
M2C_UNK ov00_021E9210();
extern M2C_UNK data_ov031_0224e5e8;

void ov00_021E7D48(void) {
    if (M2C_FIELD(&data_ov031_0224e5e8, void **, 8) == NULL) {
        return;
    }
    _Z9LockMutexP5Mutex(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x13D8);
    M2C_FIELD(M2C_FIELD(&data_ov031_0224e5e8, void **, 8), s32 *, 0x13F0) = 1;
    _Z11UnlockMutexP5Mutex(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x13D8);
    if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5e8, void **, 8), s32 *, 0x1314) != 0) {
        ov00_021E9210();
    }
    if (M2C_FIELD(M2C_FIELD(&data_ov031_0224e5e8, void **, 8), s32 *, 0x1384) == 0) {
        return;
    }
    _Z22AwaitContextCompletionP16ProcessorContext(M2C_FIELD(&data_ov031_0224e5e8, void **, 8) + 0x1318);
}
