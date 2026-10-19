#include <m2c.h>


u8 func_020965ac(s32 arg0, u32 arg1) {
    if (arg1 < 0xCCU) {
        return M2C_FIELD((arg0 + arg1), u8 *, 0xAC);
    }
    return 0xFFU;
}
