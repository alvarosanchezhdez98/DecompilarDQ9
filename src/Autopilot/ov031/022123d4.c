#include <m2c.h>

s32 WCM_GetPhase();
M2C_UNK func_ov031_02211e08();
M2C_UNK ov00_021EC24C(M2C_UNK, s32);
s32 ov00_021EC9A8();
u32 ov00_021FAA40();

s32 func_ov031_022123d4(void) {
    u32 var_r4;

    func_ov031_02211e08();
    if (ov00_021EC9A8() != 0) {
        var_r4 = ov00_021FAA40();
        if ((var_r4 == 0xFF) || (var_r4 > 0x63U)) {
            var_r4 = 0x63;
        }
        if (WCM_GetPhase() == 0xB) {
            ov00_021EC24C(9, 0xFFFF298C - var_r4);
        } else {
            ov00_021EC24C(8, 0xFFFF2D10 - var_r4);
        }
        return 1;
    }
    return 0;
}
