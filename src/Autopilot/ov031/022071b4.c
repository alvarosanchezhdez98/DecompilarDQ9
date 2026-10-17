#include <m2c.h>

s32 SOCLi_SocketGetNextPtr(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov031_0224e230;

s32 SOCL_SocketIsInTrash(M2C_UNK arg0) {
    if (SOCLi_SocketGetNextPtr(&data_ov031_0224e230, arg0) != 0) {
        return 1;
    }
    return 0;
}
