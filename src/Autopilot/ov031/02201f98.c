#include <m2c.h>

M2C_UNK tcp_send_handshake(M2C_UNK, M2C_UNK, M2C_UNK);

void tcp_send_finack(M2C_UNK arg0, M2C_UNK arg1) {
    tcp_send_handshake(arg0, 0x11, arg1);
}
