#include <m2c.h>

u16 *func_02012fe4();
M2C_UNK func_0201ba1c(u16 *, u16, u16);
void *func_ov017_0218b5b0();

void func_ov017_021cfe84(s32 arg0, void *arg1) {
    u16 *temp_r0;

    temp_r0 = func_02012fe4();
    if (M2C_FIELD(arg1, u16 *, 4) != *temp_r0) {
        return;
    }
    if (M2C_FIELD(M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3734), u8 *, 3) != 0) {
        return;
    }
    func_0201ba1c(temp_r0, M2C_FIELD(arg1, u16 *, 8), M2C_FIELD(arg1, u16 *, 6));
}
