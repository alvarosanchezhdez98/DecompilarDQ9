#include <m2c.h>

M2C_UNK func_020469b4(s32, void *);
M2C_UNK func_0206e348(s32 *, M2C_UNK, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021baedc(void *, M2C_UNK);
M2C_UNK *func_0205ec34(void);

s32 func_ov004_02167fd4(void) {
    s32 temp_r4;
    void *temp_r0;
    void *temp_r5;

    temp_r0 = func_ov017_0218b5b0();
    temp_r5 = M2C_FIELD(temp_r0, void **, 0x3734);
    temp_r4 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    func_ov017_021baedc(temp_r5, 1);
    M2C_FIELD(temp_r5, s16 *, 8) = 0x6FAE;
    func_020469b4(temp_r4, temp_r5);
    func_0206e348(func_0205ec34(), 0x17, 1);
    return 0;
}
