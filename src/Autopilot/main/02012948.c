#include <m2c.h>

M2C_UNK func_020cdac4(M2C_UNK (*)());
M2C_UNK func_020cdae4(M2C_UNK, M2C_UNK, void *, M2C_UNK);
M2C_UNK func_020ce0fc(M2C_UNK);
M2C_UNK func_020ce114(M2C_UNK);
M2C_UNK func_0201289c(void *);
M2C_UNK func_02012bbc();

void func_02012938(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;

    func_020cdac4(func_02012bbc);
    M2C_FIELD(arg0, s8 *, 0x62) = 1;
    func_0201289c(arg0);
    func_020cdae4(0, 1, arg0, 4);
    func_020ce0fc(2);
    func_020ce114(2);
    M2C_FIELD(arg0, s8 *, 0x60) = 0;
    M2C_FIELD(arg0, u8 *, 0x5F) = (u8) M2C_FIELD(arg0, u8 *, 0x63);
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) M2C_FIELD(arg0, s32 *, 0x64);
    temp_r0 = M2C_FIELD(arg0, s32 *, 0x68);
    if (temp_r0 >= 0) {
        M2C_FIELD(arg0, s32 *, 0x30) = temp_r0;
    }
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 0x6C);
    if (temp_r0_2 >= 0) {
        M2C_FIELD(arg0, s32 *, 0x34) = temp_r0_2;
    }
}
