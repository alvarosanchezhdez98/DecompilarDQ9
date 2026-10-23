#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState20GetUnknownGameObjectEv(s32);
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, s32);
M2C_UNK func_02010828(s32);
M2C_UNK func_020397cc(void *, M2C_UNK);
s32 func_0203b5a0(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_021d2c34(s32, M2C_UNK, M2C_UNK);

void func_020a8c4c(void *arg0, s32 arg1) {
    s32 temp_r10;
    s32 temp_r9;
    void *temp_r4;
    void *temp_r8;

    if (M2C_FIELD(arg0, u8 *, 4) & (1 << arg1)) {
        return;
    }
    temp_r10 = _ZN9GameState11GetInstanceEv();
    temp_r9 = func_ov017_0218b5b0();
    temp_r8 = _ZN9GameState20GetUnknownGameObjectEv(temp_r10);
    temp_r4 = _ZN9GameState21GetPartyMemberByIndexEi(temp_r10, arg1);
    func_02010828(temp_r10);
    if (func_0203b5a0(temp_r9, 0) == 0) {
        func_020397cc(temp_r4, 1);
        M2C_FIELD(temp_r4, s16 *, 0xAC) = 0;
        if (arg1 == M2C_FIELD(temp_r8, s16 *, 4)) {
            return;
        }
        func_ov017_021d2c34(arg1, 0, 0);
        return;
    }
    M2C_FIELD(arg0, u8 *, 4) = (u8) (M2C_FIELD(arg0, u8 *, 4) | (1 << arg1));
    M2C_FIELD(temp_r4, s16 *, 0xAC) = (s16) (0 - M2C_FIELD(arg0, s32 *, 0xC));
    M2C_FIELD(temp_r4, u8 *, 0xC1) = (u8) (M2C_FIELD(temp_r4, u8 *, 0xC1) | 8);
}
