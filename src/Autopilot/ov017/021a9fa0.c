#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_020100f8(s32);
u16 *func_02012fe4();
s32 func_0201b5d8(u16);
M2C_UNK func_020a27ac();
M2C_UNK func_020e1154(M2C_UNK);
M2C_UNK func_ov017_0218b5b0();

void func_ov017_021a9fa0(void *arg0) {
    s32 temp_r5;
    u16 *temp_r4;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    func_ov017_0218b5b0();
    temp_r4 = func_02012fe4();
    func_020100f8(temp_r5);
    func_020a27ac();
    if (func_0201b5d8(*temp_r4) != 0) {
        func_020e1154(0x3E8);
    }
    M2C_FIELD(arg0, s8 *, 1) = 1;
}
