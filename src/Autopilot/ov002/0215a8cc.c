#include <m2c.h>

void *func_ov017_0218b5b0();
M2C_UNK func_ov002_0215a920(void *);

s32 func_ov002_0215a8cc(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x253C) == 0) {
        return 0;
    }
    M2C_FIELD(arg0, s16 *, 0x1BE0) = (s16) M2C_FIELD(arg0, s32 *, 0x2540);
    M2C_FIELD(arg0, s16 *, 0x1BFE) = (s16) M2C_FIELD(arg0, s32 *, 0x2544);
    func_ov002_0215a920(arg0 + 0x253C);
    func_ov002_0215a920(M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x371C) + 0x24);
    return 1;
}
