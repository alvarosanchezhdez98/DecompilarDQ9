#include <m2c.h>

M2C_UNK func_0205d6a0();
s8 func_0205d794();
M2C_UNK func_0205deb4();
M2C_UNK func_0205eaa0();
M2C_UNK func_020dd4c4();
M2C_UNK func_ov000_02176634();
M2C_UNK func_ov000_02176e3c();
s32 func_ov000_0217c594();
s32 func_ov000_0217c5f4();
M2C_UNK func_ov000_0217c638();
s32 func_ov000_0217f8c0();
s32 func_ov000_021815c8();
s32 func_ov000_021815e4();
extern M2C_UNK data_02108760;

void func_ov000_0217db4c(void *arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r7_2;
    s8 temp_r0;
    s8 temp_r7;

    M2C_FIELD(arg0, u16 *, 0x1D72) = (u16) (M2C_FIELD(arg0, u16 *, 0x1D72) | 0x100);
    func_0205deb4(arg0 + 0x188, 0x21, 0);
    temp_r7 = M2C_FIELD(arg0, s8 *, 0x1D6F);
    temp_r0 = func_0205d794(arg0 + 0x188);
    M2C_FIELD(arg0, s8 *, 0x1D6F) = temp_r0;
    if (temp_r7 == temp_r0) {
        if (func_ov000_0217c594(arg0, 5) != 0) {
            M2C_FIELD(arg0, s8 *, 0x956) = 0;
            func_0205eaa0(&data_02108760, 1);
            M2C_FIELD(arg0, s8 *, 0x240) = 7;
            temp_r7_2 = func_ov000_021815e4(arg0);
            func_020dd4c4(func_ov000_021815c8(arg0), temp_r7_2);
            M2C_FIELD(arg0, s8 *, 0x1D68) = (s8) (M2C_FIELD(arg0, s8 *, 0x1D68) + 1);
            M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60) = 0x20;
            func_ov000_02176634(arg0, func_ov000_0217f8c0(arg0), M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60), arg1, arg2);
            return;
        }
        if (func_ov000_0217c5f4(arg0) != 0) {
            M2C_FIELD(arg0, s8 *, 0x956) = 0;
            func_0205d6a0(arg0 + 0x188);
            func_0205d6a0(arg0 + 0x188, 0);
            M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60) = 0;
            M2C_FIELD(arg0, s8 *, 0x1D68) = (s8) (M2C_FIELD(arg0, s8 *, 0x1D68) - 1);
            func_ov000_0217c638(arg0, arg1, arg2);
            func_ov000_02176e3c(arg0, func_ov000_0217f8c0(arg0), M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x1D68)), s8 *, 0x1D60), arg1, arg2, 0);
        }
    }
}
