#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, s32);
M2C_UNK func_ov017_021c9d2c(s32, s16, s16, s16, s32, s32, s32, s32, s32);

void func_ov000_0217616c(void *arg0) {
    if (func_0200ff1c(_ZN9GameState11GetInstanceEv(), M2C_FIELD(arg0, s32 *, 0x4C)) != 0) {
        func_ov017_021c9d2c(M2C_FIELD(arg0, s32 *, 0x4C), M2C_FIELD(arg0, s16 *, 0xC), M2C_FIELD(arg0, s16 *, 8), M2C_FIELD(arg0, s16 *, 0xE), (s32) M2C_FIELD(arg0, s16 *, 0xA), M2C_FIELD(arg0, s32 *, 0x28), 0, 0, 0);
    }
}
