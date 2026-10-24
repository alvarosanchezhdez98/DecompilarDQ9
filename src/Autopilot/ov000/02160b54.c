#include <m2c.h>

M2C_UNK _ZN12RenderConfig12SubmitToFifoEv();
M2C_UNK _ZN8Object3D4DrawEb(s32, M2C_UNK);
M2C_UNK _ZN8Object3D8SetScaleEPK8Vector3i(s32, M2C_UNK *);
M2C_UNK _ZN8Vector3iaSERKS_(s32, s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s16);
M2C_UNK _ZNK8Object3D8GetScaleEv(M2C_UNK *, s32);
M2C_UNK func_020100bc(s32);
M2C_UNK func_02016874(void *);
s32 func_0203b4fc(s32, M2C_UNK);
s32 func_020a1fa8();
M2C_UNK func_ov000_02161020(void *);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov025_021df864(void *);

void func_ov000_02160b54(void *arg0) {
    M2C_UNK sp0[3];
    s32 temp_r6;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r0;

    temp_r6 = _ZN9GameState11GetInstanceEv();
    temp_r5 = func_ov017_0218b5b0();
    func_020100bc(temp_r6);
    if (M2C_FIELD(arg0, s32 *, 0x55F4) & 0x200) {
        if (func_0203b4fc(temp_r5, 0x100000) == 0) {
            func_02016874(arg0 + 0xEC8);
        }
        func_ov000_02161020(arg0);
        if (func_0203b4fc(temp_r5, 4) == 0) {
            temp_r5_2 = _ZN9GameState20GetGameObjectByIndexEi(temp_r6, M2C_FIELD(arg0, s16 *, 0x6FD6));
            temp_r0 = _ZN9GameState20GetGameObjectByIndexEi(temp_r6, 0xC8);
            if (temp_r0 != 0) {
                if (temp_r5_2 != 0) {
                    _ZN8Vector3iaSERKS_(temp_r0 + 0x44, temp_r5_2 + 0x44);
                    _ZN8Vector3iaSERKS_(temp_r0 + 0x50, temp_r5_2 + 0x50);
                    _ZNK8Object3D8GetScaleEv(sp0, temp_r5_2);
                    _ZN8Object3D8SetScaleEPK8Vector3i(temp_r0, sp0);
                }
                _ZN8Object3D4DrawEb(temp_r0, 0);
            }
        }
        _ZN12RenderConfig12SubmitToFifoEv();
        if ((M2C_FIELD(arg0, s32 *, 0xEA8) == 8) && (func_020a1fa8() == 4)) {
            func_ov025_021df864(arg0 + 0x5AB0);
        }
    }
}
