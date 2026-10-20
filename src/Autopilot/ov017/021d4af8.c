#include <m2c.h>

M2C_UNK exit(M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, s32);

s32 func_ov017_021d4af8(void *arg0, void *arg1, s32 arg2) {
    s32 temp_r2;
    s32 temp_r3;
    u32 temp_r6;
    void *temp_r2_2;

    temp_r6 = M2C_FIELD(arg0, u32 *, 0x28);
    if (temp_r6 >= (u32) M2C_FIELD(arg0, u32 *, 0x2C)) {
        exit(-2);
    }
    M2C_FIELD(temp_r6, s32 *, 0) = arg2;
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0x28), void **, 8) = (void *) M2C_FIELD(arg0, void **, 0x34);
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0x28), s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x30);
    temp_r2 = M2C_FIELD(arg0, s32 *, 0x14) - (M2C_FIELD(arg1, s32 *, 0xC) * 8);
    M2C_FIELD(arg0, s32 *, 0x30) = temp_r2;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_r2 + (M2C_FIELD(arg1, s32 *, 8) * 8));
    M2C_FIELD(arg0, void **, 0x34) = arg1;
    M2C_FIELD(arg0, u32 *, 0x28) = (u32) (M2C_FIELD(arg0, u32 *, 0x28) + 0xC);
    temp_r2_2 = M2C_FIELD(arg0, void **, 0x34);
    temp_r3 = M2C_FIELD(temp_r2_2, s32 *, 0xC);
    memset(M2C_FIELD(arg0, s32 *, 0x30) + (temp_r3 * 8), 0, (M2C_FIELD(temp_r2_2, s32 *, 8) - temp_r3) * 8);
    return M2C_FIELD(arg0, s32 *, 0x48) + M2C_FIELD(arg1, s32 *, 0);
}
