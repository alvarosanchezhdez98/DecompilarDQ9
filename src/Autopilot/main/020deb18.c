#include <m2c.h>


s16 func_020deb08(void *arg0) {
    u16 temp_r0;
    u16 var_r1;

    var_r1 = M2C_FIELD(arg0, u16 *, 0);
    temp_r0 = M2C_FIELD(arg0, u16 *, 4);
    if ((s32) var_r1 <= (s32) temp_r0) {
        var_r1 = temp_r0;
    }
    return (s16) var_r1;
}
