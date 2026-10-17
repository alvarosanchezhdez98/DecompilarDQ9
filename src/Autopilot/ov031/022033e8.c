#include <m2c.h>

M2C_UNK CPSi_SslShutdown(void *);
M2C_UNK CPSi_TcpShutdownRaw(void *);
extern M2C_UNK data_02111304;

void CPS_TcpShutdown(void) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(M2C_FIELD(&data_02111304, void **, 4), void **, 0xA4);
    if (temp_r4 == NULL) {
        return;
    }
    if (M2C_FIELD(temp_r4, u8 *, 9) != 0) {
        CPSi_SslShutdown(temp_r4);
    }
    CPSi_TcpShutdownRaw(temp_r4);
}
