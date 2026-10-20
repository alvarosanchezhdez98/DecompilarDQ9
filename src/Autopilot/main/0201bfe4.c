#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
void *_ZN9GameState15GetGrottoStructEv();
s32 func_0201b588(u16);
extern u16 data_020fb3f0;

void func_0201bfd4(void) {
    void *temp_r4;

    _ZN9GameState11GetInstanceEv();
    temp_r4 = _ZN9GameState15GetGrottoStructEv();
    if (func_0201b588(data_020fb3f0) != 0) {
        return;
    }
    if (M2C_FIELD(temp_r4, u8 *, 4) != 0) {
        M2C_FIELD(temp_r4, s8 *, 3) = 0;
        M2C_FIELD(temp_r4, u8 *, 4) = 0U;
    }
}
