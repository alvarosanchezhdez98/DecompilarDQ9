#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetUnknownGameObjectEv();
s32 func_020100f8(s32);
M2C_UNK func_02033b58(s32, M2C_UNK);
M2C_UNK func_02033e2c(s32);
M2C_UNK func_020397c0();
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_020a27ac();
s32 func_ov017_0218b5b0();

void func_ov017_021bff2c(void) {
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = _ZN9GameState20GetUnknownGameObjectEv();
    func_020397c0();
    func_02033e2c(temp_r4);
    func_02033b58(temp_r4, 0);
    temp_r4_2 = func_ov017_0218b5b0();
    if (func_020100f8(temp_r5) != 0) {
        func_020a27ac();
    }
    if (temp_r4_2 == 0) {
        return;
    }
    func_0203b4e8(temp_r4_2, 0x80);
}
