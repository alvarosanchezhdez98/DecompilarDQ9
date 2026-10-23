#include <m2c.h>

M2C_UNK SOCLi_ExecCommandPacket(s32, M2C_UNK);
s32 SOCLi_GetCtrlPipe(void *arg0);

void func_ov031_0220529c(void *arg0, M2C_UNK arg1) {
    SOCLi_ExecCommandPacket(SOCLi_GetCtrlPipe(arg0), arg1);
}
