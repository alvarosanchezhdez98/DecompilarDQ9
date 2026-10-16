#include <m2c.h>

s32 *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
M2C_UNK func_ov000_02169b78();
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_02169e54(void) {
    *_ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 8) = 4;
    func_ov000_02169b78();
    return 1;
}
