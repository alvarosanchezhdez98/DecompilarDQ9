#include <m2c.h>

s32 tcp_write_do(M2C_UNK, s32, s32, s32);

void tcp_write_do2(M2C_UNK arg0, s32 arg1, M2C_UNK arg2, s32 arg3, s32 arg4, s32 arg5) {
    if ((tcp_write_do(arg0, arg1, arg4, arg5) != 0) && (arg3 != 0)) {
        tcp_write_do(arg2, arg3, arg4, 0);
    }
}
