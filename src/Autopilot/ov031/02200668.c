#include <m2c.h>


s32 invert_checksum(s32 arg0) {
    u16 var_r0;

    var_r0 = arg0 ^ 0xFFFF;
    if (var_r0 == 0) {
        var_r0 = 0xFFFF;
    }
    return (s32) var_r0;
}
