#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState20GetGameObjectByIndexEi(s32, M2C_UNK);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0218fcf8(s32, M2C_UNK);

void func_ov017_021bdb78(M2C_UNK arg0) {
    s32 temp_r4;
    s32 temp_r5;
    void *temp_r0;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    temp_r4 = func_ov017_0218b5b0();
    temp_r0 = _ZN9GameState20GetGameObjectByIndexEi(temp_r5, arg0);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s16 *, 0x9C) = 0x40C8;
    func_ov017_0218fcf8(temp_r4, 0);
}
