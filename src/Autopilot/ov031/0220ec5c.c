#include <m2c.h>

void *WcmAllocApList();
M2C_UNK WcmAppendApList(void *);
void *WcmGetOldestApList();
void *WcmSearchApList(void *);
M2C_UNK func_020ca4b4(void *, void *, M2C_UNK);
void *func_ov031_0220d60c();

void WCMi_EntryApList(void *arg0, s16 arg1) {
    void *temp_r0;
    void *var_r7;

    temp_r0 = func_ov031_0220d60c();
    if (temp_r0 == NULL) {
        return;
    }
    if ((M2C_FIELD(temp_r0, u8 *, 0x226A) == 0) && (M2C_FIELD(arg0, u16 *, 0x3C) == 0)) {
        var_r7 = WcmSearchApList(arg0 + 4);
        if (var_r7 == NULL) {
            var_r7 = WcmAllocApList();
        }
        if ((var_r7 == NULL) && (M2C_FIELD(temp_r0, s32 *, 0x2278) == 1)) {
            var_r7 = WcmGetOldestApList();
        }
        if (var_r7 == NULL) {
            return;
        }
        M2C_FIELD(var_r7, s16 *, 2) = arg1;
        func_020ca4b4(arg0, var_r7 + 0x10, 0xC0);
        WcmAppendApList(var_r7);
    }
}
