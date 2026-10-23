#include <m2c.h>

s32 func_020421a0();
M2C_UNK func_02046380();
M2C_UNK func_02046574(s32, M2C_UNK, s32);
void *func_0208d994(s32, s32);
s32 func_ov004_021666bc(M2C_UNK, M2C_UNK *);
extern s32 data_ov004_0217101c;

s32 func_ov004_02167310(M2C_UNK arg0) {
    M2C_UNK sp0;
    s32 temp_r4;
    s32 temp_r5;
    void *temp_r0;

    temp_r5 = data_ov004_0217101c;
    temp_r4 = func_020421a0();
    func_02046380();
    temp_r0 = func_0208d994(temp_r5 + 0xC, func_ov004_021666bc(arg0, &sp0));
    if (temp_r0 != NULL) {
        func_02046574(temp_r4, 0, M2C_FIELD(temp_r0, s32 *, 4));
    }
    return 0;
}
