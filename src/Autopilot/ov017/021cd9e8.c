#include <m2c.h>

s32 _ZN9GameState20GetGameObjectByIndexEi(M2C_UNK, s32);
s32 _ZNK8Object3D10GetField06Ev();
s32 func_0202c1a4(s32);
M2C_UNK func_ov017_021c4fa0(u32, s32);
M2C_UNK func_ov017_021cdaa0();
M2C_UNK func_ov017_021cf730(s8, M2C_UNK);

void func_ov017_021cd9e8(s32 arg0, void *arg1, M2C_UNK arg2, s32 arg3, s32 arg4) {
    s32 var_r6;

    if (func_0202c1a4(arg4) != ((u32) (M2C_FIELD(arg1, u8 *, 4) << 0x1C) >> 0x1C)) {
        return;
    }
    if (M2C_FIELD(arg1, s32 *, 8) & 1) {
        func_ov017_021cdaa0();
    }
    if (M2C_FIELD(arg1, s32 *, 8) & 0x20) {
        func_ov017_021cf730((s8) ((u32) (M2C_FIELD(arg1, u8 *, 4) << 0x18) >> 0x1C), 0);
    }
    var_r6 = -1;
    if ((M2C_FIELD(arg1, s32 *, 8) & 0x10) && (_ZN9GameState20GetGameObjectByIndexEi(arg2, func_0202c1a4(arg4)) != 0)) {
        var_r6 = _ZNK8Object3D10GetField06Ev();
    }
    if (!(M2C_FIELD(arg1, s32 *, 8) & 4)) {
        return;
    }
    func_ov017_021c4fa0((u32) (M2C_FIELD(arg1, u8 *, 4) << 0x18) >> 0x1C, var_r6);
}
