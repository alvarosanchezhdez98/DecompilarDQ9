#include <m2c.h>

s32 func_02012444(M2C_UNK *, s32);
M2C_UNK func_0205d1e0(void *);
M2C_UNK func_0205d274(void *);
M2C_UNK func_0205d2bc(void *);
M2C_UNK func_0205d6a0(void *, M2C_UNK);
M2C_UNK func_ov000_02174b14(void *);
M2C_UNK func_ov000_0217a8f4(void *);
M2C_UNK func_ov000_02180404(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;

void func_ov000_0217e46c(void *arg0) {
    if ((func_02012444(&data_02114e30, 0x802) == 0) && (M2C_FIELD(&data_02114e54, u8 *, 0x55) == 0)) {
        return;
    }
    func_ov000_02180404(arg0);
    func_ov000_02174b14(arg0);
    func_ov000_0217a8f4(arg0);
    M2C_FIELD(arg0, s32 *, 0x920) = 0x100;
    M2C_FIELD(arg0, s32 *, 0x92C) = 8;
    M2C_FIELD(arg0, s32 *, 0x924) = 0x100;
    M2C_FIELD(arg0, s32 *, 0x928) = 0x100;
    M2C_FIELD(arg0, u16 *, 0x1D72) = (u16) (M2C_FIELD(arg0, u16 *, 0x1D72) & ~0x38);
    func_ov000_02174b14(arg0);
    memset(arg0 + 0x1D60, 0, 8);
    M2C_FIELD(arg0, s8 *, 0x1D68) = 0;
    M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60) = 1;
    func_0205d1e0(arg0 + 0x188);
    func_0205d274(arg0 + 0x188);
    func_0205d2bc(arg0 + 0x188);
    func_0205d6a0(arg0 + 0x188, 1);
    M2C_FIELD(arg0, u16 *, 0x1D72) = (u16) (M2C_FIELD(arg0, u16 *, 0x1D72) | 2);
}
