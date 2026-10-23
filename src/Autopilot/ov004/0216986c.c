#include <m2c.h>

M2C_UNK func_0205eaa0(M2C_UNK *, M2C_UNK, M2C_UNK);
void *func_ov004_02168aa0(void *, M2C_UNK);
M2C_UNK func_ov004_0216920c(void *);
extern M2C_UNK data_02108760;
extern void *data_ov004_02171030;
void _ZN10MenuScript10StartEntryEi(void *, s32);
void _ZN10MenuScript9SetUnk1b0Et(void *, u16);
void _ZN16MenuObjectClass110SetPaletteEa(void *, s8);

s32 func_ov004_0216986c(void *arg0) {
    void *temp_r0;

    temp_r0 = func_ov004_02168aa0(arg0, 0x1E);
    if (temp_r0 == NULL) {
        return 0;
    }
    _ZN16MenuObjectClass110SetPaletteEa(temp_r0, 2);
    _ZN10MenuScript9SetUnk1b0Et(arg0, 0x64U);
    func_ov004_0216920c(arg0);
    _ZN10MenuScript10StartEntryEi(arg0, 0x46);
    if (M2C_FIELD(data_ov004_02171030, u8 *, 0x1A0) == 0) {
        func_0205eaa0(&data_02108760, 1, 0);
    }
    M2C_FIELD(data_ov004_02171030, u8 *, 0x1A0) = 1U;
    return 0;
}
