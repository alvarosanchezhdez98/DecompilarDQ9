#include <m2c.h>

s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_02191aac(s32, M2C_UNK, s16, M2C_UNK);
M2C_UNK func_ov017_021ce014(M2C_UNK, M2C_UNK, M2C_UNK, u16);

void func_02083c48(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s8 *, 0x56C) = 0;
    if (arg2 != 0) {
        func_ov017_02191aac(func_ov017_0218b5b0(), 0, M2C_FIELD(arg0, s16 *, 0x568), 2);
    }
    if (arg1 == 0) {
        return;
    }
    func_ov017_021ce014(0, 1, 0, (u16) M2C_FIELD(arg0, s16 *, 0x568));
}
