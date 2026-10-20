#include <m2c.h>

s32 func_0202ae18();
s32 func_0202ae24();
M2C_UNK func_0202b0f4(s32);
M2C_UNK func_0203b4a0(void *, M2C_UNK);
M2C_UNK func_0203b4b0(void *, M2C_UNK);
M2C_UNK func_020466e4(s32, M2C_UNK);
M2C_UNK func_0205e854(s32);
s32 func_020936f8();
M2C_UNK func_020939fc(s32);
s32 func_0209494c();
s32 func_020d6c00();
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_02192594(void *);
M2C_UNK func_ov017_02195748(void *);

u8 func_ov017_021af4ec(void *arg0) {
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r6;
    s32 temp_r8;
    void *temp_r7;

    temp_r5 = func_020d6c00();
    temp_r8 = func_020936f8();
    if (func_0209494c() != 0) {
        func_020466e4(temp_r5, 0x20);
        temp_r7 = func_ov017_0218b5b0();
        temp_r6 = func_0202ae18();
        temp_r5_2 = func_0202ae24();
        M2C_FIELD(arg0, s8 *, 0xF) = 0;
        func_0203b4a0(temp_r7, 2);
        func_0202b0f4(temp_r6);
        func_ov017_02195748(temp_r7);
        func_ov017_02192594(temp_r7);
        func_020939fc(temp_r8);
        func_0205e854(temp_r5_2);
        func_0203b4b0(temp_r7, 0x40);
        M2C_FIELD(temp_r7, s8 *, 0x42E3) = 0;
        M2C_FIELD(temp_r7, s8 *, 0x42E2) = 0;
        M2C_FIELD(arg0, s8 *, 1) = 1;
    }
    return M2C_FIELD(arg0, u8 *, 8);
}
