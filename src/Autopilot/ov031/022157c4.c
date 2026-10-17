#include <m2c.h>

s32 memcmp(M2C_UNK, M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov031_02249b48;

s32 ov00_021FD1C8(M2C_UNK arg0) {
    if (memcmp(arg0, &data_ov031_02249b48, 8) == 0) {
        return 1;
    }
    return 0;
}
