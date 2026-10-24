#include <m2c.h>

M2C_UNK func_ov031_022157f8(M2C_UNK, M2C_UNK *);
s32 memcmp(M2C_UNK *, M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov031_02249b3c;

s32 ov00_021FD11C(M2C_UNK arg0) {
    M2C_UNK sp0[6];

    func_ov031_022157f8(arg0, sp0);
    if (memcmp(sp0, &data_ov031_02249b3c, 8) == 0) {
        return 1;
    }
    return 0;
}
