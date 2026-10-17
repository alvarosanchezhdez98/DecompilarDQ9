#include <m2c.h>
#pragma optimization_level 4

s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK9GameState12GetTickCountEv(s32);
s32 func_0200fb08();
M2C_UNK func_0205a330(s32, s32);
M2C_UNK func_0205a370(s32, M2C_UNK);
void *func_0205a3d0(s32, M2C_UNK);
M2C_UNK func_0205a42c(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0205ae8c(void *);
M2C_UNK func_020e27ec(s32, M2C_UNK, M2C_UNK, M2C_UNK);

void func_ov003_0216ddfc(void *arg0) {
    s32 temp_r0_2;
    s32 temp_r4;
    s32 temp_r5;
    void *temp_r0;
    void *temp_r0_3;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    if (M2C_FIELD(arg0, u8 *, 0x13EC) & 4) {
        temp_r5 = M2C_FIELD(arg0, s32 *, 0x12A8);
        if (temp_r5 != 0) {
            func_0205a370(temp_r5, 1);
            temp_r0 = func_0205a3d0(temp_r5, 1);
            if (temp_r0 != NULL) {
                M2C_FIELD(temp_r0, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x15) | 8);
            }
            func_0205a330(temp_r5, _ZNK9GameState12GetTickCountEv(temp_r4));
            func_020e27ec(temp_r5, 1, 0xDF, 0x96);
            func_0205a42c(temp_r5, 1, 0x10);
            _ZN9GameState11GetInstanceEv();
            if (func_0200fb08() == 3) {
                func_020e27ec(temp_r5, 1, 0xD7, 0x96);
            }
        }
        func_0205ae8c(arg0 + 0x126C);
        return;
    }
    temp_r0_2 = M2C_FIELD(arg0, s32 *, 0x12A8);
    if (temp_r0_2 == 0) {
        return;
    }
    temp_r0_3 = func_0205a3d0(temp_r0_2, 1);
    if (temp_r0_3 != NULL) {
        M2C_FIELD(temp_r0_3, u8 *, 0x15) = (u8) (M2C_FIELD(temp_r0_3, u8 *, 0x15) & ~8);
    }
}
