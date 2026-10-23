#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState20GetGameObjectByIndexEi(s32, s8);
void *func_02012fe4();
s32 func_0202ae18();
s32 func_0202b7d8(s32);
s32 func_0202c508(s32);
M2C_UNK func_020469b4(s32, void *);
void *func_02052e2c();
M2C_UNK func_ov003_02161480();
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_02195530(void *);
M2C_UNK func_ov017_021bbae4(void *, s32, M2C_UNK);

void func_ov003_02163d7c(void *arg0) {
    s32 temp_r4_2;
    s32 temp_r5;
    s32 temp_r7;
    void *temp_r0;
    void *temp_r4;
    void *temp_r5_2;
    void *temp_r6;
    void *temp_r8;

    func_ov003_02161480();
    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_02012fe4();
    temp_r0 = func_ov017_0218b5b0();
    temp_r6 = temp_r0;
    temp_r7 = M2C_FIELD(temp_r6, s32 *, 0x36FC);
    temp_r8 = M2C_FIELD(temp_r6, void **, 0x3734);
    _ZN9GameState20GetGameObjectByIndexEi(temp_r5, M2C_FIELD(arg0, s8 *, 0x4A2));
    temp_r5_2 = func_02052e2c();
    temp_r4_2 = func_0202ae18();
    func_ov017_021bbae4(temp_r8, M2C_FIELD(temp_r4, s32 *, 8), 1);
    M2C_FIELD(temp_r8, s8 *, 0xCD) = (s8) M2C_FIELD(arg0, s8 *, 0x4A2);
    M2C_FIELD(temp_r8, s8 *, 0xCE) = (s8) ((u32) (M2C_FIELD(temp_r5_2, u8 *, 0x14) << 0x1F) >> 0x1F);
    M2C_FIELD(temp_r8, s8 *, 0xCF) = 0;
    func_020469b4(temp_r7, temp_r8);
    M2C_FIELD(arg0, s8 *, 0x4A3) = 0x10;
    M2C_FIELD(arg0, s32 *, 0x464) = (s32) (M2C_FIELD(arg0, s32 *, 0x464) & ~0x8000);
    if (func_0202b7d8(temp_r4_2) == 0) {
        return;
    }
    if (func_0202c508(temp_r4_2) == 0) {
        return;
    }
    func_ov017_02195530(temp_r6);
}
