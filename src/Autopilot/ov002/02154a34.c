#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *func_0200ff1c(s32, M2C_UNK);

s32 func_ov002_02154a34(s32 arg0, M2C_UNK arg1) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = func_0200ff1c(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 == NULL) {
        return 0;
    }
    var_r0 = 0;
    if ((s32) M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x130), u16 *, 4) > 0) {
        var_r0 = 1;
    }
    return var_r0;
}
