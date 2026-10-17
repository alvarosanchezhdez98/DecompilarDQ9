#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
M2C_UNK func_ov031_02243b34(void *);

s32 func_ov031_022436e0(void *arg0) {
    _ZN9GameState11GetInstanceEv();
    func_ov031_02243b34(arg0);
    if (M2C_FIELD(arg0, u8 *, 0x36) != 0) {
        return 2;
    }
    return 1;
}
