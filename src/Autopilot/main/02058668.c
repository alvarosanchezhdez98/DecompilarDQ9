#include <m2c.h>


s32 func_02058658(s32 arg0, s32 arg1) {
    s32 temp_r2;

    temp_r2 = arg1 - 0xD0;
    if ((temp_r2 < 0) || (temp_r2 >= 0x10)) {
        return 0;
    }
    return (temp_r2 * 0xD4) + (arg0 + 8);
}
