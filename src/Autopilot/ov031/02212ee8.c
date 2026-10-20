#include <m2c.h>

s32 _Z20DisableIRQInterruptsv();
M2C_UNK _Z20SetIRQInterruptStatei();
M2C_UNK ov00_021FAE6C();
u32 ov00_021FAECC();
M2C_UNK ov00_021FAFD8();
s32 ov00_021FB010();
u32 ov00_021FB6B8();
u32 ov00_021FBD38();
u32 ov00_021FC32C();
u32 ov00_021FC408();
u32 ov00_021FCBD8();
u32 ov00_021FCC60();

s32 ov00_021FA904(void) {
    s32 temp_r4;
    s32 temp_r4_2;
    u32 var_r5;

    var_r5 = ov00_021FAECC();
    if (var_r5 == 1) {
        var_r5 = ov00_021FCBD8();
    } else if (var_r5 < 7U) {
        temp_r4_2 = _Z20DisableIRQInterruptsv();
        var_r5 = ov00_021FC408();
        ov00_021FAE6C();
        _Z20SetIRQInterruptStatei(temp_r4_2);
    } else if (var_r5 < 9U) {
        var_r5 = ov00_021FB6B8();
    } else if (var_r5 < 0xAU) {
        var_r5 = ov00_021FC32C();
    } else if (var_r5 < 0x10U) {
        var_r5 = ov00_021FCC60();
    } else if (var_r5 == 0x11) {
        var_r5 = ov00_021FBD38();
    }
    ov00_021FAE6C(var_r5);
    if (var_r5 == 0x10) {
        temp_r4 = ov00_021FB010();
        ov00_021FAFD8();
        return temp_r4;
    }
    if (var_r5 != 0x12) {
        return 0;
    }
    ov00_021FAFD8();
    return -1;
}
