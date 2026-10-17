#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState20GetUnknownGameObjectEv(s32);
s32 func_020100f8(s32);
M2C_UNK func_020397c0();
M2C_UNK func_0203b4e8(s32, M2C_UNK);
M2C_UNK func_020a27ac();
M2C_UNK func_020a28b0(s32, M2C_UNK);
M2C_UNK func_ov003_0217f118(void *);
s32 func_ov017_0218b5b0();

void func_ov003_0217f1b8(void *arg0) {
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_ov017_0218b5b0();
    func_ov003_0217f118(arg0);
    _ZN9GameState20GetUnknownGameObjectEv(temp_r4);
    func_020397c0();
    temp_r4_2 = func_020100f8(temp_r4);
    func_020a27ac();
    func_020a28b0(temp_r4_2, 2);
    func_0203b4e8(temp_r5, 0xC0);
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
