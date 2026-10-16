#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *func_0200ff94(s32, s32);
s32 func_0206f4f0(s32, s16);

s32 func_ov000_02153758(void *arg0, s32 arg1) {
    s32 var_r0;
    void *temp_r0;

    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        return 0;
    }
    temp_r0 = func_0200ff94(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 == NULL) {
        return 0;
    }
    return func_0206f4f0(M2C_FIELD(arg0, s32 *, 0x8E18) + 0x678, M2C_FIELD(temp_r0, s16 *, 2));
}
