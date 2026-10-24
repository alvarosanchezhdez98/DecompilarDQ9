#include <m2c.h>

M2C_UNK func_020469b4(s32, void *);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021a8670(void *);
M2C_UNK func_ov017_021a932c(void *, M2C_UNK);

void func_ov017_021a8614(s32 arg0, M2C_UNK arg1, s8 arg2, s8 arg3, s32 arg4, s32 arg5) {
    s32 temp_r4;
    void *temp_r0;
    void *temp_r5;

    temp_r0 = func_ov017_0218b5b0();
    temp_r5 = M2C_FIELD(temp_r0, void **, 0x3B7C);
    temp_r4 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    func_ov017_021a8670(temp_r5);
    func_ov017_021a932c(temp_r5, arg1);
    M2C_FIELD(temp_r5, s8 *, 0x18) = arg2;
    M2C_FIELD(temp_r5, s8 *, 0x19) = arg3;
    M2C_FIELD(temp_r5, s8 *, 0x1A) = (s8) arg4;
    M2C_FIELD(temp_r5, s8 *, 0x1B) = (s8) arg5;
    func_020469b4(temp_r4, temp_r5);
}
