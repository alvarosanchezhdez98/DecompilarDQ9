#include <m2c.h>

M2C_UNK _ZN13HMRFAllocator4FreeEi(s32, M2C_UNK);
s32 func_ov017_021d60f4();
extern s32 *data_ov001_021658b8[8];

s32 func_ov001_02161900(void) {
    s32 *temp_r0;

    temp_r0 = data_ov001_021658b8[func_ov017_021d60f4()];
    if (temp_r0 != NULL) {
        _ZN13HMRFAllocator4FreeEi(*temp_r0, 1);
    }
    return 1;
}
