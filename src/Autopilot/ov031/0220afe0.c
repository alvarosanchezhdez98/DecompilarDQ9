#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);

void CPSi_md5_init(void *arg0) {
    VectorizedMemset(arg0, 0, 0x58);
    M2C_FIELD(arg0, s32 *, 0) = 0x67452301;
    M2C_FIELD(arg0, s32 *, 4) = 0xEFCDAB89;
    M2C_FIELD(arg0, s32 *, 8) = 0x98BADCFE;
    M2C_FIELD(arg0, s32 *, 0xC) = 0x10325476;
}
