#include <m2c.h>

M2C_UNK CPSi_sha1_calc(M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK char_from_long__sha1(M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_022498e5;

void CPSi_sha1_result_prng(M2C_UNK arg0, M2C_UNK arg1) {
    CPSi_sha1_calc(arg0, &data_ov031_022498e5, 0x2C);
    char_from_long__sha1(arg1, arg0, 0x14);
}
