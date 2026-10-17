#include <m2c.h>

M2C_UNK _Z18SetMenuObjectFlagsP10MenuScriptth(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK _ZN10MenuScript10StartEntryEi(M2C_UNK, s32);
s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_020421a0();
M2C_UNK func_02043204();
s32 func_ov017_021b213c(s32, s32);
extern M2C_UNK data_ov004_021707d8;

s32 func_ov004_021589e8(M2C_UNK arg0) {
    if (func_ov017_021b213c(M2C_FIELD((_ZN9GameState11GetInstanceEv() + 0x5E6C), s32 *, 0xF4), M2C_FIELD(M2C_FIELD(&data_ov004_021707d8, void **, 8), s32 *, 0x18)) != 0) {
        func_020421a0();
        func_02043204();
        _ZN10MenuScript10StartEntryEi(arg0, 0x387);
    } else {
        _ZN10MenuScript10StartEntryEi(arg0, 0x3A2);
    }
    _Z18SetMenuObjectFlagsP10MenuScriptth(arg0, 2, 8);
    return 0;
}
