#include <m2c.h>

s32 _ZN9GameState20GetGameObjectByIndexEi(M2C_UNK, M2C_UNK);
s32 _ZN9GameState20GetUnknownGameObjectEv(M2C_UNK);
s32 _ZNK8Object3D10GetField06Ev(s32);
M2C_UNK func_020a86b8(M2C_UNK, M2C_UNK, u8, u8, s32, s32, s32, s32, s32);

void func_ov017_021d18d8(M2C_UNK arg0, void *arg1, M2C_UNK arg2) {
    M2C_UNK var_r8;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r7;

    temp_r6 = _ZN9GameState20GetGameObjectByIndexEi(arg2, arg0);
    var_r8 = 1;
    temp_r7 = _ZN9GameState20GetUnknownGameObjectEv(arg2);
    temp_r6_2 = _ZNK8Object3D10GetField06Ev(temp_r6);
    if (temp_r6_2 != _ZNK8Object3D10GetField06Ev(temp_r7)) {
        var_r8 = 0;
    }
    func_020a86b8(arg0, var_r8, M2C_FIELD(arg1, u8 *, 4), M2C_FIELD(arg1, u8 *, 5), (s32) M2C_FIELD(arg1, u8 *, 6), (s32) M2C_FIELD(arg1, u8 *, 7), (s32) M2C_FIELD(arg1, u8 *, 8), (s32) M2C_FIELD(arg1, u8 *, 9), M2C_FIELD(arg1, s32 *, 0xC));
}
