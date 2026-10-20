#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
u16 *func_02012fe4();
M2C_UNK func_020469b4(s32, s32);
s32 func_02046b38(s32, s32);
s32 func_02046b60(s32, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021b6f18(s32);
M2C_UNK func_ov017_021b7104(s32, void *);

void func_ov017_021a7b38(void *arg0) {
    s32 temp_r4;
    s32 temp_r5;
    u16 temp_r6;
    void *temp_r0;

    _ZN9GameState11GetInstanceEv();
    temp_r0 = func_ov017_0218b5b0();
    temp_r4 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    temp_r5 = M2C_FIELD(temp_r0, s32 *, 0x3718);
    temp_r6 = *func_02012fe4();
    if (M2C_FIELD(arg0, s32 *, 8) != 0) {
        return;
    }
    if (func_02046b60(temp_r4, 3) != 0) {
        M2C_FIELD(arg0, s8 *, 1) = 1;
        return;
    }
    if ((M2C_FIELD(arg0, u8 *, 0x1A) != 0) && ((((s32) temp_r6 / 100) * 0x64) != 0x170C) && (temp_r6 != 0x2710)) {
        M2C_FIELD(arg0, s8 *, 1) = 1;
        return;
    }
    if (func_02046b38(temp_r4, temp_r5) == 0) {
        M2C_FIELD(arg0, s32 *, 0x20) = 1;
        func_ov017_021b6f18(temp_r5);
        func_ov017_021b7104(temp_r5, arg0 + 0xC);
        func_020469b4(temp_r4, temp_r5);
    }
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
