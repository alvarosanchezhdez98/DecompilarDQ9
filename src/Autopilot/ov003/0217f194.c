#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_ov003_0216d7ec();
M2C_UNK func_ov017_0218b5b0();

void func_ov003_0217f194(void *arg0) {
    _ZN9GameState11GetInstanceEv();
    func_ov017_0218b5b0();
    if (M2C_FIELD(arg0, s32 *, 0xC) == 0) {
        return;
    }
    func_ov003_0216d7ec();
}
