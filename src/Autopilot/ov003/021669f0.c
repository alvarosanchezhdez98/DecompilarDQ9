#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState14GetProtagonistEv(s32);
s32 func_02010828();
M2C_UNK func_020397cc(s32, M2C_UNK);
s32 func_0205ec34();
M2C_UNK func_0206df6c(s32, s32, s32, M2C_UNK);
M2C_UNK func_02086a04(s32, s8);
s32 func_ov003_02166a90(void *, s16);

s32 func_ov003_021669f0(void *arg0) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r4;
    s32 temp_r5;

    if ((s32) M2C_FIELD(arg0, s16 *, 0x480) < 0) {
        return 1;
    }
    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_02010828();
    temp_r0 = func_ov003_02166a90(arg0, M2C_FIELD(arg0, s16 *, 0x480));
    if (temp_r0 == 0) {
        return 0;
    }
    if (temp_r0 == 1) {
        func_02086a04(temp_r4, (s8) M2C_FIELD(arg0, s16 *, 0x480));
        temp_r0_2 = func_0205ec34();
        func_0206df6c(temp_r0_2, temp_r0_2 + 0x8C, 0x784, 1);
    }
    temp_r0_3 = _ZN9GameState14GetProtagonistEv(temp_r5);
    if (temp_r0_3 != 0) {
        func_020397cc(temp_r0_3, 1);
    }
    return 1;
}
