#include <m2c.h>

s32 func_0202bcbc();

s32 func_0202c178(s32 arg0) {
    s32 temp_r0;

    temp_r0 = func_0202bcbc();
    if (temp_r0 < 0) {
        return 0;
    }
    return (0x74 * temp_r0) + (arg0 + 0xBC0);
}
