#include <m2c.h>

M2C_UNK _Z17SetMainBrightnessP13GameResourcesii(s32, M2C_UNK, M2C_UNK);
s32 _Z28IsBrightnessTransitionActiveP13GameResources(s32);
s32 _ZN9GameState11GetInstanceEv();
void *func_0200ff1c(s32, s32);
s32 func_020100b0();
s32 func_0203b57c(s32, M2C_UNK);
void *func_020421a0();
M2C_UNK func_02046380(void *);
M2C_UNK func_02046574(void *, M2C_UNK, s32);
s32 func_020e0434(void *, s16);
M2C_UNK func_ov003_02159250(void *, s32);
s32 func_ov017_0218b5b0();

void func_ov003_0215af9c(void *arg0) {
    void *temp_r7_3;
    void *temp_r4;
    u8 temp_r5;
    s32 temp_r7_2;

    s32 temp_r7;
    temp_r7 = func_ov017_0218b5b0();
    temp_r4 = func_020421a0();
    temp_r5 = M2C_FIELD(arg0, u8 *, 0x580);
    if (temp_r5 == 0) {
        if ((_Z28IsBrightnessTransitionActiveP13GameResources(temp_r7) == 0) && (func_0203b57c(temp_r7, 0) != 0) && (func_0203b57c(temp_r7, 1) != 0)) {
            _Z17SetMainBrightnessP13GameResourcesii(temp_r7, 0, 0xF);
        }
        M2C_FIELD(arg0, u8 *, 0x580) = (u8) (M2C_FIELD(arg0, u8 *, 0x580) + 1);
    }
    if (temp_r5 == 1) {
        if (M2C_FIELD(arg0, u8 *, 0x59D) != 0) {
            return;
        }
        if (_Z28IsBrightnessTransitionActiveP13GameResources(temp_r7) != 0) {
            return;
        }
        if (func_0203b57c(temp_r7, 0) != 0) {
            return;
        }
        if (M2C_FIELD(arg0, u8 *, 0x587) == 1) {
            temp_r7_2 = _ZN9GameState11GetInstanceEv();
            temp_r7_3 = func_0200ff1c(temp_r7_2, func_020100b0());
            func_02046380(temp_r4);
            func_02046574(temp_r4, 0, M2C_FIELD(temp_r7_3, s32 *, 0x134));
        }
        M2C_FIELD(temp_r4, s32 *, 0x998) = 1;
        func_ov003_02159250(arg0, func_020e0434(arg0 + 0x64, (s16) (M2C_FIELD(arg0, u8 *, 0x587) + 0x438)));
        M2C_FIELD(arg0, u8 *, 0x580) = (u8) (M2C_FIELD(arg0, u8 *, 0x580) + 1);
        goto block_16;
    }
block_16:
    if ((temp_r5 == 2) && (M2C_FIELD(temp_r4, s32 *, 0x998) == 0)) {
        M2C_FIELD(arg0, s8 *, 0x588) = 0xB;
        M2C_FIELD(arg0, u8 *, 0x580) = 0U;
    }
}
