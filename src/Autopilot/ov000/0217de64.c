#include <m2c.h>

M2C_UNK func_02092b34(void *);
s32 func_02092bcc(void *, s32);
M2C_UNK func_ov000_02176e3c(void *, M2C_UNK, s8, M2C_UNK, s32, s32);
M2C_UNK func_ov000_0217c638(void *, M2C_UNK, s32);

void func_ov000_0217de64(void *arg0, M2C_UNK arg1, s32 arg2) {
    M2C_FIELD(arg0, u16 *, 0x1D72) = (u16) (M2C_FIELD(arg0, u16 *, 0x1D72) & ~0x100);
    if (func_02092bcc(arg0 + 0x7C, M2C_FIELD(arg0, s32 *, 0x94C)) != 0) {
        func_02092b34(arg0 + 0x7C);
        M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60) = 0;
        M2C_FIELD(arg0, s8 *, 0x1D68) = (s8) (M2C_FIELD(arg0, s8 *, 0x1D68) - 1);
        func_ov000_02176e3c(arg0, 0, M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60), arg1, arg2, 0);
        func_ov000_0217c638(arg0, arg1, arg2);
    }
}
