#include <m2c.h>

M2C_UNK SOCLi_ExecCommandPacket(s32);

void SOCLi_ExecCommandPacketInRecvPipe(void *arg0) {
    SOCLi_ExecCommandPacket(M2C_FIELD(arg0, s32 *, 0x64));
}
