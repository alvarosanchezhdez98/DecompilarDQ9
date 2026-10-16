#include <m2c.h>


void SOCLi_SocketRegisterList(void **arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x7C) = (void *) *arg0;
    *arg0 = arg1;
}
