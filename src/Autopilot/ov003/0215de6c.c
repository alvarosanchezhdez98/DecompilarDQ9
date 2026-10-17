#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *func_02010828(s32);
s32 func_020421a0();
M2C_UNK func_02046380(s32);
M2C_UNK func_020465c0(s32, M2C_UNK, s32);
M2C_UNK func_020465d8(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020465f0(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_02046608(s32, M2C_UNK, s32, M2C_UNK, s32, s32, s32);
s32 func_020e51cc(s32);

void func_ov003_0215de6c(void *arg0, M2C_UNK arg1) {
    s32 temp_r4;
    s32 temp_r5;
    s32 var_r4;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_020421a0();
    var_r4 = M2C_FIELD(func_02010828(temp_r4), s32 *, 0xF6C);
    if (M2C_FIELD(arg0, u8 *, 0x3BB) == 2) {
        var_r4 -= M2C_FIELD(arg0, s32 *, 0x3CC);
    }
    func_02046380(temp_r5);
    func_020465c0(temp_r5, 0, var_r4);
    func_020465f0(temp_r5, 0, 7);
    func_020465d8(temp_r5, 0, 1);
    func_02046608(temp_r5, 8, func_020e51cc(0x3F1), arg1, 0x100, 0, 0);
}
