#include <m2c.h>

M2C_UNK CPS_SslAddRandomSeed(M2C_UNK *, M2C_UNK);
M2C_UNK func_020c9b10(M2C_UNK *);
extern M2C_UNK data_ov031_0229199c;

void ov38_022230BC(void) {
    func_020c9b10(&data_ov031_0229199c);
    CPS_SslAddRandomSeed(&data_ov031_0229199c, 0x20);
}
