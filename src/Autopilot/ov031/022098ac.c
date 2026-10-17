#include <m2c.h>

M2C_UNK CPSi_md5_calc(s32, M2C_UNK, M2C_UNK);
M2C_UNK CPSi_sha1_calc(s32);

void update_digest(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    CPSi_sha1_calc(arg0 + 0x2EC);
    CPSi_md5_calc(arg0 + 0x3A4, arg1, arg2);
}
