#include <m2c.h>

s32 _ZN10MenuScript10GetObjectsEv();
s32 _ZN14MenuObjectList4FindEi(s32, M2C_UNK);
s32 _ZN15MenuObjectClass7GetTypeEv();
M2C_UNK _ZN17MenuObjectClass107SetItemEs(s32, s16);
s32 func_0205ec34();
s32 func_0206dfb0(s32, s32, s32);
void *func_ov004_021551a8(M2C_UNK);

s32 func_ov004_021552b8(M2C_UNK arg0) {
    s32 temp_r0;
    s16 var_r5;
    s32 temp_r0_3;
    u16 temp_r6;
    void *temp_r0_2;

    temp_r0 = _ZN14MenuObjectList4FindEi(_ZN10MenuScript10GetObjectsEv(), 0x2E);
    if (temp_r0 == 0) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv() != 0x10) {
        return 0;
    }
    temp_r0_2 = func_ov004_021551a8(arg0);
    var_r5 = -1;
    if (temp_r0_2 != NULL) {
        var_r5 = M2C_FIELD(temp_r0_2, s16 *, 0x18);
        temp_r6 = (u16) ((u32) (M2C_FIELD(temp_r0_2, s32 *, 0xC) << 9) >> 0x15);
        if ((s32) temp_r6 > 0) {
            temp_r0_3 = func_0205ec34();
            if (func_0206dfb0(temp_r0_3, temp_r0_3 + 0x8C, temp_r6 + 0xC76) == 0) {
                var_r5 = -1;
            }
        }
    }
    _ZN17MenuObjectClass107SetItemEs(temp_r0, var_r5);
    return 0;
}
