#include <m2c.h>
#pragma optimization_level 4

s32 _ZN9GameState11GetInstanceEv();
void *func_02010828(s32);
M2C_UNK func_02042058(s32, s32);
s32 func_020421a0();
M2C_UNK func_02046380(s32);
M2C_UNK func_020465c0(s32, M2C_UNK, s32);
M2C_UNK func_020465d8(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020465f0(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK func_0205de24(s32, M2C_UNK, M2C_UNK);
s32 func_020e51cc(s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov003_0215b478(void *arg0) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_020421a0();
    func_0205de24(arg0 + 0xF4, 0, 2);
    M2C_FIELD(arg0, s16 *, 0x194) = 0xB;
    M2C_FIELD(arg0, s16 *, 0x196) = 2;
    M2C_FIELD(arg0, s16 *, 0x198) = 0x14;
    M2C_FIELD(arg0, s16 *, 0x19A) = 0;
    M2C_FIELD(arg0, s16 *, 0x19C) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x19E) = 2;
    M2C_FIELD(arg0, s16 *, 0x1A0) = 0xA;
    M2C_FIELD(arg0, s16 *, 0x1A2) = 0xE;
    M2C_FIELD(arg0, s8 *, 0x1A5) = 0;
    M2C_FIELD(arg0, s8 *, 0x1A9) = 1;
    memset(M2C_FIELD(arg0, s32 *, 0x7C), 0, 0x960);
    func_02042058(M2C_FIELD(arg0, s32 *, 0x7C), func_020e51cc(0x3F1));
    func_02046380(temp_r4);
    func_020465c0(temp_r4, 0, M2C_FIELD(func_02010828(temp_r5), s32 *, 0xF6C));
    func_020465f0(temp_r4, 0, 7);
    func_020465d8(temp_r4, 0, 1);
    func_0205d304(arg0 + 0xF4, M2C_FIELD(arg0, s32 *, 0x7C), 0, 0, 0, 1, 0, 0);
}
