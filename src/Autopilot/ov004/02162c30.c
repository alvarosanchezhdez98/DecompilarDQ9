#include <m2c.h>

M2C_UNK _Z17CallMenuObjectVf0P10MenuScriptti(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_ov004_0215eb40(void *);
s32 func_ov004_0215f74c(void *, s32);
M2C_UNK func_ov004_0215fdfc(void *);
extern M2C_UNK data_02108760;
extern M2C_UNK data_ov004_021707e8;
extern M2C_UNK data_ov004_02170b90;
void _ZN10MenuScript10StartEntryEi(void *, s32);

s32 func_ov004_02162c30(void *arg0) {
    u32 temp_r0;

    if (M2C_FIELD(&data_ov004_021707e8, u8 *, 0) == 1) {
        return 0;
    }
    if (func_ov004_0215f74c(arg0, M2C_FIELD(&data_ov004_021707e8, s32 *, 0x1C)) == 0) {
        func_ov004_0215fdfc(arg0);
        return 0;
    }
    M2C_FIELD(&data_ov004_021707e8, u8 *, 0) = 1U;
    temp_r0 = M2C_FIELD(&data_ov004_021707e8, u8 *, 7) - 0x64;
    switch (temp_r0) {
    default:
        break;
    case 0:
        M2C_FIELD(&data_ov004_021707e8, s8 *, 6) = (s8) M2C_FIELD(&data_ov004_021707e8, s8 *, 5);
        _ZN10MenuScript10StartEntryEi(arg0, 0x65);
        break;
    case 1:
        M2C_FIELD(&data_ov004_021707e8, s8 *, 6) = (s8) M2C_FIELD(&data_ov004_02170b90, u8 *, 0x23F);
        _ZN10MenuScript10StartEntryEi(arg0, 0x66);
        break;
    case 2:
        M2C_FIELD(&data_ov004_021707e8, s8 *, 6) = (s8) M2C_FIELD(&data_ov004_02170b90, u8 *, 0x47F);
        func_ov004_0215eb40(arg0);
        _ZN10MenuScript10StartEntryEi(arg0, 0x67);
        break;
    case 3:
        M2C_FIELD(&data_ov004_021707e8, s8 *, 6) = 1;
        _ZN10MenuScript10StartEntryEi(arg0, 0x68);
        break;
    case 4:
        M2C_FIELD(&data_ov004_021707e8, s8 *, 6) = (s8) M2C_FIELD(&data_ov004_021707e8, s8 *, 9);
        M2C_FIELD(&data_ov004_021707e8, u8 *, 8) = (u8) M2C_FIELD(&data_ov004_021707e8, u8 *, 3);
        _ZN10MenuScript10StartEntryEi(arg0, 0x64);
        break;
    }
    M2C_FIELD(&data_ov004_02170b90, s8 *, 0x23C) = 0;
    M2C_FIELD(&data_ov004_02170b90, s8 *, 0x47C) = 0;
    M2C_FIELD(&data_ov004_021707e8, s8 *, 0xB) = 0;
    M2C_FIELD(&data_ov004_021707e8, u8 *, 0) = 0U;
    _Z17CallMenuObjectVf0P10MenuScriptti(arg0, 0x84, 1);
    func_0205eaa0(&data_02108760, 1, 0);
    return 0;
}
