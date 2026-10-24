#include <m2c.h>

M2C_UNK DWCi_BM_GetWiFiInfo(M2C_UNK *);
M2C_UNK ov00_021E89AC(M2C_UNK, M2C_UNK *);

void ov00_021E8984(M2C_UNK arg0) {
    M2C_UNK sp0[5];

    DWCi_BM_GetWiFiInfo(sp0);
    ov00_021E89AC(arg0, sp0);
}
