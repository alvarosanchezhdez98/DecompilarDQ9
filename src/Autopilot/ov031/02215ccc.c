#include <m2c.h>


u8 ov00_021FD6D0(s32 arg0) {
    s32 var_r0;

    var_r0 = arg0 >> 2;
    if (!(arg0 & 2)) {
        var_r0 += 0x19;
    }
    return (u8) var_r0;
}
