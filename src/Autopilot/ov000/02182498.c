#include <m2c.h>


void func_ov000_02182498(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        if (M2C_FIELD(arg0, u8 *, 0x6E8) == 0) {
            return;
        }
        if (M2C_FIELD(arg0, s16 *, 0x6EC) == 0) {
            M2C_FIELD(arg0, s16 *, 0x6EC) = (s16) (M2C_FIELD(arg0, s16 *, 0x6EA) + 5);
        }
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x6E8) = 0U;
    M2C_FIELD(arg0, s8 *, 0x6E9) = 0;
}
