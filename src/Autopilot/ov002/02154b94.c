#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *func_0200ff1c(s32, M2C_UNK);

s32 func_ov002_02154b94(s32 arg0, M2C_UNK arg1) {
    void *temp_r0;

    temp_r0 = func_0200ff1c(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 == NULL) {
        return 0;
    }
    if (M2C_FIELD(temp_r0, u16 *, 0x1B2) != 0) {
        return 1;
    }
    return 0;
}
