#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_02010828(s32);
s32 func_02086ef0(s32, s16);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_02191108(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32);

void func_02048150(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r8;
    s32 var_r1;
    s32 var_r3;
    s32 var_r6;
    u16 temp_r3;
    void *temp_r3_2;
    void *temp_r6;
    void *temp_r8_2;

    var_r6 = arg1;
    temp_r8 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_ov017_0218b5b0();
    temp_r0 = func_02010828(temp_r8);
    temp_r8_2 = M2C_FIELD(arg0, void **, 0x130);
    var_r1 = 0;
    if (M2C_FIELD(temp_r8_2, s32 *, 0) & 1) {
        var_r1 = 1;
    }
    temp_r3 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x134), u16 *, 0x30);
    if (var_r6 > 0) {
        if (var_r6 > (s32) temp_r3) {
            var_r6 = (s32) temp_r3;
        }
        M2C_FIELD(temp_r8_2, u16 *, 4) = (u16) var_r6;
    } else if (M2C_FIELD(temp_r8_2, u16 *, 4) == 0) {
        M2C_FIELD(temp_r8_2, u16 *, 4) = temp_r3;
    }
    temp_r6 = M2C_FIELD(arg0, void **, 0x130);
    var_r3 = 0;
    if (M2C_FIELD(temp_r6, s32 *, 0) & 4) {
        var_r3 = 1;
    }
    M2C_FIELD(temp_r6, s32 *, 0) = 0;
    if (var_r3 != 0) {
        temp_r3_2 = M2C_FIELD(arg0, void **, 0x130);
        M2C_FIELD(temp_r3_2, s32 *, 0) = (s32) (M2C_FIELD(temp_r3_2, s32 *, 0) | 4);
    }
    if (var_r1 != 0) {
        if ((func_02086ef0(temp_r0, M2C_FIELD(arg0, s16 *, 4)) != 0) && (arg2 != 0)) {
            func_ov017_02191108(temp_r4, 1, 1, 1, 1);
        }
    }
}
