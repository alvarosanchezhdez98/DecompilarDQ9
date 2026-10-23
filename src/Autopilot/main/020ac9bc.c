#include <m2c.h>

s32 _Z28IsBrightnessTransitionActiveP13GameResources(void *);
s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ffd0(s32);
M2C_UNK func_02012fe4();
void *func_02046b1c(s32);
s32 func_02046b24(s32);
M2C_UNK func_ov017_02193dc4(s32);
M2C_UNK func_020ad61c(s32);

void func_020ac9ac(void *arg0) {
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r5;
    s32 temp_r6;
    void *temp_r0;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    temp_r6 = M2C_FIELD(arg0, s32 *, 0x36FC);
    func_02012fe4();
    temp_r4_2 = func_0200ffd0(temp_r4);
    temp_r5 = func_02046b24(temp_r6);
    temp_r0 = func_02046b1c(temp_r6);
    if (temp_r4_2 == 0) {
        return;
    }
    if ((temp_r5 == 0xA) && (M2C_FIELD(temp_r0, u8 *, 3) != 0)) {
        return;
    }
    if ((temp_r5 == 3) && (_Z28IsBrightnessTransitionActiveP13GameResources(arg0) == 0)) {
        return;
    }
    func_020ad61c(temp_r4_2);
    func_ov017_02193dc4(temp_r4_2);
}
