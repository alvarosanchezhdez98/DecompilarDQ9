#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *func_02010828();
s32 func_020421a0();
M2C_UNK func_02046380();
M2C_UNK func_020465c0(s32, M2C_UNK, s32);
M2C_UNK func_020465d8(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020465f0(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_02046608(s32, M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_0205d0e0(void *, M2C_UNK);
M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
s32 func_020e51cc(s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov002_0215be00(void *, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov002_0215bf34(void *arg0) {
    s32 temp_r5;
    void *temp_r6;

    func_ov002_0215be00(arg0, 0x29, 0x15, 0x15);
    _ZN9GameState11GetInstanceEv();
    temp_r6 = func_02010828();
    temp_r5 = func_020421a0();
    func_02046380();
    func_020465c0(temp_r5, 0, M2C_FIELD(temp_r6, s32 *, 0xF6C));
    func_020465d8(temp_r5, 0, 1);
    func_020465f0(temp_r5, 0, 7);
    memset(M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0x960);
    func_02046608(temp_r5, 8, func_020e51cc(0x3F1), M2C_FIELD(arg0, s32 *, 0x1BD0), 0x100, 0, 0);
    func_0205d304(arg0 + 0xEC8, M2C_FIELD(arg0, s32 *, 0x1BD0), 0, 0, 0, 0, 0, 0);
    func_0205d0e0(arg0 + 0xEC8, 4);
}
