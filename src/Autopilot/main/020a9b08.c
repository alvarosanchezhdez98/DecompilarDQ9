#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK func_020120d4(s32, u8);
M2C_UNK memcpy(s32, void *, M2C_UNK);

s32 func_020a9af8(u8 *arg0) {
    s32 temp_r0;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    func_020120d4(temp_r0, *arg0);
    memcpy(temp_r0 + 0x5CDC, arg0 + 4, 0x190);
    return 1;
}
