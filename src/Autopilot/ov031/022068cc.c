#include <m2c.h>

s32 SOCL_SocketIsInTrash(s32);
s32 SOCL_SocketIsInvalid();

s32 SOCL_IsClosed(s32 arg0) {
    if ((arg0 >= 0) && (SOCL_SocketIsInvalid() != 0) && (SOCL_SocketIsInTrash(arg0) == 0)) {
        return 1;
    }
    return 0;
}
