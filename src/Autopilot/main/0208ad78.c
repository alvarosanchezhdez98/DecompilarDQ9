#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, M2C_UNK);
M2C_UNK func_02026f08(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_02026f20(s32, M2C_UNK);
M2C_UNK func_0202ae18();
s32 func_0202b7d8();
M2C_UNK func_020482e0(void *, u8, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021c9e00(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);

void func_0208ad68(void *arg0, M2C_UNK arg1) {
    s32 temp_r5;
    s32 temp_r6;
    u16 temp_r7;
    void *temp_r0;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r6 = M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x36D0);
    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(temp_r5, arg1);
    temp_r7 = M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x130), u16 *, 4);
    func_020482e0(temp_r0, M2C_FIELD(arg0, u8 *, 5), 0);
    if (temp_r7 != M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x130), u16 *, 4)) {
        func_02026f08(temp_r6, arg1, 1);
        func_02026f20(temp_r6, arg1);
    }
    func_0202ae18();
    if (func_0202b7d8() == 0) {
        return;
    }
    func_ov017_021c9e00(arg1, 1, 0, 1);
}
