#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
M2C_UNK memcpy(M2C_UNK, s32, M2C_UNK);
M2C_UNK memset(M2C_UNK, M2C_UNK, M2C_UNK);

s32 func_020ac460(M2C_UNK arg0) {
    memset(arg0, 0, 0x3C);
    memcpy(arg0, _ZN9GameState11GetInstanceEv() + 0x7504, 0x3C);
    return 1;
}
