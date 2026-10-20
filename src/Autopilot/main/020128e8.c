#include <m2c.h>

M2C_UNK func_020cdac4(M2C_UNK);
M2C_UNK func_020cdbe4();
M2C_UNK func_020ce0fc(M2C_UNK);
M2C_UNK func_020ce114(M2C_UNK);
M2C_UNK func_0201289c(void *);

void func_020128d8(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;

    M2C_FIELD(arg0, u8 *, 0x63) = (u8) M2C_FIELD(arg0, u8 *, 0x5F);
    M2C_FIELD(arg0, s32 *, 0x64) = (s32) M2C_FIELD(arg0, s32 *, 0x40);
    temp_r0 = M2C_FIELD(arg0, s32 *, 0x30);
    if (temp_r0 >= 0) {
        M2C_FIELD(arg0, s32 *, 0x68) = temp_r0;
    }
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_r0_2 >= 0) {
        M2C_FIELD(arg0, s32 *, 0x6C) = temp_r0_2;
    }
    func_020cdbe4();
    func_020ce0fc(4);
    func_020ce114(4);
    func_020cdac4(0);
    func_0201289c(arg0);
    M2C_FIELD(arg0, s8 *, 0x60) = 1;
}
