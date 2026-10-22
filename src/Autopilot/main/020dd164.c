#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, M2C_UNK);
void *func_02053c6c();
s32 func_020dd19c(u8, M2C_UNK);

s32 func_020dd154(M2C_UNK arg0, M2C_UNK arg1) {
    void *temp_r0;

    if (func_0200ff1c(_ZN9GameState11GetInstanceEv(), arg0) == 0) {
        return 0;
    }
    temp_r0 = func_02053c6c();
    if (temp_r0 == NULL) {
        return 0;
    }
    return func_020dd19c((u8) M2C_FIELD(temp_r0, s32 *, 0x950), arg1);
}
