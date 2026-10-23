#include <m2c.h>

M2C_UNK SOCLi_SendCommandPacket(s32, M2C_UNK);
s32 SOCLi_GetCtrlPipe(void *arg0);

void func_ov031_022051f4(void *arg0, M2C_UNK arg1) {
    SOCLi_SendCommandPacket(SOCLi_GetCtrlPipe(arg0), arg1);
}
