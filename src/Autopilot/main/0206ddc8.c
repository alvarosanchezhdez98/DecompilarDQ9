#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_0206de40(void *);

void func_0206ddb8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x332) = 0;
    memset(arg0 + 0x8C, 0, 0x234);
    memset(arg0 + 0x2C0, 0, 0xC);
    func_0206de40(arg0);
    memset(arg0 + 0x2CC, 0, 0x66);
    memset(arg0 + 0x334, 0, 0xCE);
    M2C_FIELD(arg0, s32 *, 0x404) = 0;
    M2C_FIELD(arg0, s32 *, 0x408) = 0;
    memset(arg0 + 0x40C, 0, 0xF);
    memset(arg0 + 0x41B, 0, 0x40);
}
