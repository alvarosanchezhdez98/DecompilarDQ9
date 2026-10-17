#include <m2c.h>

s32 func_02012f24(u16);
s32 func_02012f68(u32);
s32 func_0205ec34();
s32 func_0206dfb0(s32, s32, s32);

s32 func_0201bb78(u16 *arg0, u32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r4;
    s32 var_r7;

    temp_r4 = func_0205ec34();
    var_r7 = 0;
    if ((arg1 >= 0x4E20U) && (arg1 <= 0x752FU)) {
        temp_r0 = func_02012f68(arg1);
        if (temp_r0 >= 0) {
            var_r7 = func_0206dfb0(temp_r4, temp_r4 + 0x8C, temp_r0 + 0xA5A);
        }
    } else if ((arg1 >= 0x64U) && (arg1 <= 0x270FU)) {
        temp_r0_2 = (s32) arg1 / 100;
        if (temp_r0_2 < 0x64) {
            var_r7 = func_0206dfb0(temp_r4, temp_r4 + 0x8C, temp_r0_2 + 0xA96);
        }
    } else if (arg1 == 0x2710) {
        var_r7 = func_0206dfb0(temp_r4, temp_r4 + 0x8C, 0x2B);
    } else {
        temp_r0_3 = func_02012f24(*arg0);
        if (temp_r0_3 >= 0) {
            var_r7 = func_0206dfb0(temp_r4, temp_r4 + 0x8C, temp_r0_3 + 0xA5A);
        }
    }
    return var_r7;
}
