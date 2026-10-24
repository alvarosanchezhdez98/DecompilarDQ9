#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState21GetPartyMemberByIndexEi(s32, s8);
M2C_UNK func_0202ae18();
s32 func_0202b7d8();
M2C_UNK func_ov017_021c9e00(s8, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov003_02155740(void *arg0) {
    s32 var_r0;
    s32 var_r6;
    s32 temp_r7;
    s32 temp_r8;
    void *temp_r0;
    void *temp_r6;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), M2C_FIELD(arg0, s8 *, 0x1F7));
    if (temp_r0 == NULL) {
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x1FC) & 1) {
        temp_r6 = M2C_FIELD(temp_r0, void **, 0x134);
        temp_r7 = M2C_FIELD(temp_r6, u16 *, 0x30);
        var_r6 = (s32) (M2C_FIELD(arg0, f32 *, 0x330) * (f32) temp_r7);
        temp_r8 = M2C_FIELD(temp_r6, u16 *, 0x32);
        var_r0 = (s32) (M2C_FIELD(arg0, f32 *, 0x334) * (f32) temp_r8);
        if (var_r6 <= 0) {
            var_r6 = 1;
        }
        if (var_r0 <= 0) {
            var_r0 = 0;
        }
        if ((s32) temp_r7 < var_r6) {
            var_r6 = (s32) temp_r7;
        }
        M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x130), u16 *, 4) = (u16) var_r6;
        if ((s32) temp_r8 < var_r0) {
            var_r0 = (s32) temp_r8;
        }
        M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x130), u16 *, 6) = (u16) var_r0;
    } else {
        M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x130), u16 *, 4) = (u16) M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x134), u16 *, 0x30);
        M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x130), u16 *, 6) = (u16) M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x134), u16 *, 0x32);
    }
    func_0202ae18();
    if (func_0202b7d8() == 0) {
        return;
    }
    func_ov017_021c9e00(M2C_FIELD(arg0, s8 *, 0x1F7), 1, 0, 1);
}
