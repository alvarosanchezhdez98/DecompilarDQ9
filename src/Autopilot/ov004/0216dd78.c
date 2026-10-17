#include <m2c.h>

s32 _ZN10MenuScript10GetObjectsEv();
M2C_UNK _ZN10MenuScript10StartEntryEi(M2C_UNK, s32);
void *_ZN14MenuObjectList4FindEi(s32, s32);
s32 _ZN15MenuObjectClass7GetTypeEv();
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
s32 _ZN16MenuObjectClass48GetTextsEv(void *);
s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_02012028(s32, M2C_UNK);
void *func_020421a0();
M2C_UNK func_0204500c(void *, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020466f4(s32, M2C_UNK);
s32 func_02072a68(s32, s32);
s32 func_020ab7a8(void *, M2C_UNK);
s32 func_020d6c00();
extern M2C_UNK data_ov004_02171034;

s32 func_ov004_0216dd78(M2C_UNK arg0) {
    s32 temp_r0;
    s32 temp_r0_4;
    s32 temp_r4;
    s32 temp_r6;
    s32 temp_r7;
    s32 var_r8;
    void *temp_r0_2;
    void *temp_r0_3;
    void *temp_r5;

    temp_r0 = _ZN10MenuScript10GetObjectsEv();
    temp_r0_2 = _ZN14MenuObjectList4FindEi(temp_r0, 0x192);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv() != 4) {
        return 0;
    }
    temp_r7 = _ZN16MenuObjectClass48GetTextsEv(temp_r0_2);
    temp_r6 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_020421a0();
    temp_r4 = func_020d6c00();
    _ZN16BackgroundLoader13AddLockGlobalEv();
    _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
    var_r8 = 1;
    temp_r0_3 = _ZN14MenuObjectList4FindEi(temp_r0, 2);
    if (temp_r0_3 == NULL) {
        return 0;
    }
    if (_ZN15MenuObjectClass7GetTypeEv() != 0xB) {
        return 0;
    }
    M2C_FIELD(temp_r0_3, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_3, u8 *, 0xC) & ~8);
    M2C_FIELD(temp_r5, s8 *, 0x19CA) = 0;
    M2C_FIELD(temp_r5, s8 *, 0x19AF) = 0;
    temp_r0_4 = func_020ab7a8(M2C_FIELD(&data_ov004_02171034, void **, 0x10), 1);
    if (temp_r0_4 == 5) {
        func_020466f4(temp_r4, 0x80);
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        _ZN10MenuScript10StartEntryEi(arg0, 0x194);
        var_r8 = 0;
    } else if (temp_r0_4 == 1) {
        func_020466f4(temp_r4, 0x80);
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        func_0204500c(temp_r5, func_02072a68(temp_r7, 0x5DC), 0, 0xE3);
        func_02012028(temp_r6, 0);
        var_r8 = 0;
    } else if (temp_r0_4 == 2) {
        func_020466f4(temp_r4, 0x80);
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        func_0204500c(temp_r5, func_02072a68(temp_r7, 0x5DD), 0, 0xE3);
        func_02012028(temp_r6, 0);
        var_r8 = 0;
    } else if (temp_r0_4 == 3) {
        func_020466f4(temp_r4, 0x80);
        M2C_FIELD(M2C_FIELD(&data_ov004_02171034, void **, 0x10), s8 *, 1) = 0;
        _ZN10MenuScript10StartEntryEi(arg0, 0x195);
        var_r8 = 0;
    }
    if (var_r8 == 0) {
        M2C_FIELD(temp_r0_3, u8 *, 0xC) = (u8) (M2C_FIELD(temp_r0_3, u8 *, 0xC) | 8);
    }
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
    return var_r8;
}
