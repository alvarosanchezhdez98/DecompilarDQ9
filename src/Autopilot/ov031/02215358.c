#include <m2c.h>

s32 SOC_Startup(s32);
s32 ov00_021FAE14(M2C_UNK);
M2C_UNK ov00_021FAEE8(M2C_UNK);
M2C_UNK ov00_021FCF2C(s32, M2C_UNK, s32);
extern s32 data_ov031_0224e1c0;

s32 ov00_021FCD5C(M2C_UNK arg0) {
    s32 temp_r0;
    s32 temp_r5;

    temp_r5 = ov00_021FAE14(1);
    temp_r0 = ov00_021FAE14(4);
    ov00_021FCF2C(temp_r5, arg0, temp_r0);
    data_ov031_0224e1c0 = 4;
    if (SOC_Startup(temp_r0) == 0) {
        return 0xC;
    }
    ov00_021FAEE8(2);
    return 0x11;
}
