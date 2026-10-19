#include <m2c.h>

s32 WCM_CompareBssID(s32, s32);
void *func_ov031_0220d60c();

void *WcmSearchApList(s32 arg0) {
    void *temp_r0;
    void *temp_r0_2;
    void *temp_r1;
    void *var_r4;

    temp_r0 = func_ov031_0220d60c();
    temp_r0_2 = temp_r0 + 0x2000;
    var_r4 = NULL;
    temp_r1 = M2C_FIELD(temp_r0, void **, 0x2270);
    if (arg0 == 0) {
        return NULL;
    }
    if ((temp_r1 != NULL) && ((u32) M2C_FIELD(temp_r0_2, u32 *, 0x274) > 0xCU)) {
        var_r4 = M2C_FIELD(temp_r1, void **, 4);
        if (var_r4 != NULL) {
loop_5:
            if (WCM_CompareBssID(var_r4 + 0x14, arg0) == 0) {
                var_r4 = M2C_FIELD(var_r4, void **, 0xC);
                if (var_r4 != NULL) {
                    goto loop_5;
                }
            }
        }
    }
    return var_r4;
}
