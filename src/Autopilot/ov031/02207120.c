#include <m2c.h>

s32 *SOCLi_SocketGetNextPtr();

void SOCLi_SocketUnregisterList(s32 arg0, void *arg1) {
    s32 *temp_r0;

    temp_r0 = SOCLi_SocketGetNextPtr();
    if (temp_r0 != NULL) {
        *temp_r0 = M2C_FIELD(arg1, s32 *, 0x7C);
    }
}
