#include <m2c.h>

s32 SOCLi_CreateCommandPacket(M2C_UNK *, s32, M2C_UNK);
s32 SOCLi_StartupSocket();
M2C_UNK func_ov031_0220529c(s32, s32);
extern M2C_UNK SOCLi_CreateSocketCallBack;

s32 SOCL_CreateSocket(void) {
    s32 temp_r0;

    temp_r0 = SOCLi_StartupSocket();
    if (temp_r0 == 0) {
        return -0x31;
    }
    func_ov031_0220529c(temp_r0, SOCLi_CreateCommandPacket(&SOCLi_CreateSocketCallBack, temp_r0, 1));
    return temp_r0;
}
