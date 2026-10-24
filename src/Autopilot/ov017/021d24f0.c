#include <m2c.h>

M2C_UNK _ZN9GameState20GetUnknownGameObjectEv(M2C_UNK);
s32 _ZNK8Object3D10GetField06Ev();
M2C_UNK func_020469b4(s32, void *);
s32 func_02046b60(s32, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021c2b28(void *, M2C_UNK, u8);

void func_ov017_021d24f0(s32 arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_r6;
    void *temp_r0;
    void *temp_r5;

    temp_r0 = func_ov017_0218b5b0();
    temp_r6 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    if (func_02046b60(temp_r6, 0xA) != 0) {
        return;
    }
    _ZN9GameState20GetUnknownGameObjectEv(arg2);
    if (M2C_FIELD(arg1, s32 *, 8) != _ZNK8Object3D10GetField06Ev()) {
        return;
    }
    if (func_02046b60(temp_r6, 0x1A) == 0) {
        temp_r5 = M2C_FIELD(temp_r0, void **, 0x3BB0);
        if (M2C_FIELD(temp_r5, u8 *, 2) == 0) {
            func_ov017_021c2b28(temp_r5, 1, M2C_FIELD(arg1, u8 *, 4));
            func_020469b4(temp_r6, temp_r5);
        }
    }
}
