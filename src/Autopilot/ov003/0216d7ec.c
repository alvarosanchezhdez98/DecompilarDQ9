#include <m2c.h>

M2C_UNK func_ov003_0215caa4(void *);

void func_ov003_0216d7ec(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x13EC) = (u8) (M2C_FIELD(arg0, u8 *, 0x13EC) | 2);
    if (M2C_FIELD(arg0, s16 *, 4) != 3) {
        return;
    }
    func_ov003_0215caa4(arg0 + 0x14);
}
