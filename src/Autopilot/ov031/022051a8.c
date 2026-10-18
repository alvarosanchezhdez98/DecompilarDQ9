#include <m2c.h>

M2C_UNK SOCLi_FreeCommandPacket(void *);
s32 func_020c7e0c(M2C_UNK, void *, M2C_UNK);

s32 SOCLi_SendCommandPacket(M2C_UNK arg0, void *arg1) {
    M2C_UNK var_r2;
    s32 temp_r0;

    if ((arg1 == NULL) || (M2C_FIELD(arg1, s8 *, 0xD) & 1)) {
        var_r2 = 1;
    } else {
        var_r2 = 0;
    }
    temp_r0 = func_020c7e0c(arg0, arg1, var_r2);
    if (temp_r0 == 0) {
        SOCLi_FreeCommandPacket(arg1);
    }
    if (temp_r0 != 0) {
        return 0;
    }
    return -0x2A;
}
