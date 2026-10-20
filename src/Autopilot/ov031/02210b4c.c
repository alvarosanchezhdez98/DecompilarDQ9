#include <m2c.h>

M2C_UNK _Z11UnlockMutexP5Mutex(void *);
M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
M2C_UNK _Z9LockMutexP5Mutex(void *);
s32 func_ov031_02207434(s32);
M2C_UNK func_ov031_02210358(M2C_UNK, M2C_UNK);
M2C_UNK func_ov031_022103dc(M2C_UNK);
extern void *data_ov031_0224e588;

void func_ov031_02210b4c(void) {
    s32 temp_r0;
    s32 temp_r6;

    temp_r6 = M2C_FIELD(data_ov031_0224e588, s32 *, 0x1B8);
    _Z9LockMutexP5Mutex(data_ov031_0224e588 + 0x1BC);
    M2C_FIELD(data_ov031_0224e588, s32 *, 0x1B8) = -0x3B;
    _Z11UnlockMutexP5Mutex(data_ov031_0224e588 + 0x1BC);
    if (temp_r6 >= 0) {
        if (func_ov031_02207434(temp_r6) < 0) {
            func_ov031_02210358(5, -0x32);
        } else {
            do {
                _Z19SleepCurrentContextj(0x64);
                temp_r0 = func_ov031_02207434(temp_r6);
            } while (temp_r0 == -0x1A);
            if (temp_r0 != 0) {
                func_ov031_02210358(5, -0x32);
            }
        }
    }
    func_ov031_022103dc(1);
}
