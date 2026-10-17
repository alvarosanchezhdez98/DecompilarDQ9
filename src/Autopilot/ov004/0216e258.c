#include <m2c.h>

M2C_UNK _ZN10MenuScript10StartEntryEi(M2C_UNK, s32);
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
M2C_UNK _ZN16MenuObjectClass69SetUnk10cEss(s32, M2C_UNK, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_0200fb94(s32, M2C_UNK);
s32 func_020421a0();
M2C_UNK func_02043124(s32);
M2C_UNK func_02043204();
M2C_UNK func_020466f4(s32, M2C_UNK);
s32 func_020ab7a8(void *, M2C_UNK);
s32 func_020d6c00();
s32 func_ov004_0216ae9c(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov004_02171034;

s32 func_ov004_0216e258(M2C_UNK arg0) {
    s32 temp_r0;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 var_r6;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    _ZN16BackgroundLoader13AddLockGlobalEv();
    _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
    temp_r0 = func_020ab7a8(M2C_FIELD(&data_ov004_02171034, void **, 0x10), 0);
    var_r6 = 1;
    if (temp_r0 == 5) {
        func_0200fb94(temp_r5, 5);
        func_020466f4(func_020d6c00(), 0x80);
        M2C_FIELD(&data_ov004_02171034, s8 *, 2) = 0;
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        _ZN10MenuScript10StartEntryEi(arg0, 0x3E7);
        var_r6 = 0;
    } else if (temp_r0 == 1) {
        temp_r5_2 = func_020421a0();
        func_02043204();
        func_02043124(temp_r5_2);
        func_020466f4(func_020d6c00(), 0x80);
        _ZN16MenuObjectClass69SetUnk10cEss(func_ov004_0216ae9c(arg0, 0xD4), 0, 7);
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        _ZN10MenuScript10StartEntryEi(arg0, 0x1F4);
        var_r6 = 0;
    } else if (temp_r0 == 2) {
        temp_r5_3 = func_020421a0();
        func_02043204();
        func_02043124(temp_r5_3);
        func_020466f4(func_020d6c00(), 0x80);
        _ZN16MenuObjectClass69SetUnk10cEss(func_ov004_0216ae9c(arg0, 0xD4), 0, 7);
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        _ZN10MenuScript10StartEntryEi(arg0, 0x1F5);
        var_r6 = 0;
    } else if (temp_r0 == 3) {
        temp_r5_4 = func_020421a0();
        func_02043204();
        func_02043124(temp_r5_4);
        M2C_FIELD(&data_ov004_02171034, s8 *, 3) = 4;
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        func_020466f4(func_020d6c00(), 0x80);
        _ZN10MenuScript10StartEntryEi(arg0, 0x190);
        var_r6 = 0;
    }
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
    return var_r6;
}
