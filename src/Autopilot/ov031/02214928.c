#include <m2c.h>

M2C_UNK WCM_DisconnectAsync();
M2C_UNK WCM_EndSearchAsync();
u32 WCM_GetPhase();
M2C_UNK WCM_TerminateAsync();
void *ov00_021FAE14(M2C_UNK);
M2C_UNK ov00_021FAEE8(M2C_UNK);
M2C_UNK ov00_021FC568(u8);

u8 ov00_021FC32C(void) {
    u32 temp_r0;
    u8 var_r5;
    void *temp_r4;

    temp_r4 = ov00_021FAE14(0x10);
    var_r5 = 9;
    temp_r0 = WCM_GetPhase();
    switch (temp_r0) {
    default:
        break;
    case 3:
        var_r5 = M2C_FIELD(temp_r4, u8 *, 0xD0E);
        if (((u32) (M2C_FIELD(temp_r4, u8 *, 0xD0C) << 0x18) >> 0x1E) == 1) {
            var_r5 = 7;
            M2C_FIELD((temp_r4 + (M2C_FIELD(temp_r4, u8 *, 0xD13) * 4)), s8 *, 0x444) = 0;
        } else if (((u32) var_r5 >= 3U) && ((u32) var_r5 <= 5U)) {
            ov00_021FC568(var_r5);
        }
        break;
    case 6:
        WCM_EndSearchAsync();
        break;
    case 9:
        WCM_DisconnectAsync();
        break;
    case 12:
        WCM_TerminateAsync();
        ov00_021FAEE8(4);
        var_r5 = 0x11;
        break;
    case 11:
        ov00_021FAEE8(0);
        var_r5 = 0x11;
        break;
    }
    return var_r5;
}
