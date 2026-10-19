#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK _ZN9GameState14GetProtagonistEv(s32);
s32 _ZNK8Object3D10GetField06Ev();
M2C_UNK func_020100bc();
s32 func_0203b4fc(M2C_UNK, M2C_UNK);
M2C_UNK func_ov017_0218e8c8(M2C_UNK, s32, M2C_UNK);
M2C_UNK func_ov017_021973e8(M2C_UNK);
M2C_UNK func_ov017_021a1d98(M2C_UNK, s32);

void func_ov017_02196398(M2C_UNK arg0) {
    s32 temp_r4;
    s32 temp_r4_2;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    func_020100bc();
    _ZN9GameState14GetProtagonistEv(temp_r4);
    temp_r4_2 = _ZNK8Object3D10GetField06Ev();
    func_ov017_021973e8(arg0);
    if (func_0203b4fc(arg0, 4) == 0) {
        func_ov017_0218e8c8(arg0, temp_r4_2, 1);
    }
    if (func_0203b4fc(arg0, 0x10) == 0) {
        func_ov017_021a1d98(arg0, temp_r4_2);
    }
    if (func_0203b4fc(arg0, 4) != 0) {
        return;
    }
    func_ov017_0218e8c8(arg0, temp_r4_2, 2);
}
