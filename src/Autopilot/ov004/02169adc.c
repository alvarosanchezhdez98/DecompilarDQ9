#include <m2c.h>

M2C_UNK _Z18SetMenuObjectFlagsP10MenuScriptth(void *, M2C_UNK, M2C_UNK);
M2C_UNK _Z20ClearMenuObjectFlagsP10MenuScriptth(void *, M2C_UNK, M2C_UNK);
extern void *data_ov004_02171030;
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_02169adc(void *arg0) {
    u8 *temp_r0;

    _Z20ClearMenuObjectFlagsP10MenuScriptth(arg0, 0x1E, 0x18);
    _Z20ClearMenuObjectFlagsP10MenuScriptth(arg0, 0x1F, 0x18);
    _Z18SetMenuObjectFlagsP10MenuScriptth(arg0, 2, 8);
    temp_r0 = M2C_FIELD(data_ov004_02171030, u8 **, 0x190);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (*temp_r0 != 0) {
        _ZN10MenuScript10StartEntryEi(arg0, 0x48);
    }
    return 0;
}
